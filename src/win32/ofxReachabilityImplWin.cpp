//
//  ofxReachabilityImplWin.cpp
//  ofxReachability
//
//  Created by Elias Zananiri on 2015-07-02.
//  Based on http://blogs.msdn.com/b/oldnewthing/archive/2010/04/19/9998139.aspx
//

#include "ofxReachabilityImplWin.h"
#include "ofxReachability.h"

#include <synchapi.h>
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")

//--------------------------------------------------------------
ofxReachabilityImplWin::ofxReachabilityImplWin()
: ofxReachabilityImpl()
, _hWait(NULL)
, _bConnectedTest(false)
{
	ZeroMemory(&_overlapped, sizeof(_overlapped));
}

//--------------------------------------------------------------
ofxReachabilityImplWin::~ofxReachabilityImplWin()
{

}

//--------------------------------------------------------------
void ofxReachabilityImplWin::setup()
{
#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9)
	// Poco undefs Windows things cause it's stupid.
	_overlapped.hEvent = CreateEventW(NULL, FALSE, FALSE, NULL);
#else
	_overlapped.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
#endif
	if (!_overlapped.hEvent) {
		ofLogError("ofxReachabilityImplWin::setup") << "Could not create event";
		return;
	}
	if (!RegisterWaitForSingleObject(&_hWait, _overlapped.hEvent, OnChange, this, INFINITE, 0)) {
		ofLogError("ofxReachabilityImplWin::setup") << "Could not register callback";
		return;
	}

	// Get the ball rolling.
	checkIPAddress();
    
    ofAddListener(ofEvents().update, this, &ofxReachabilityImplWin::update);
}

//--------------------------------------------------------------
void ofxReachabilityImplWin::exit()
{
    ofRemoveListener(ofEvents().update, this, &ofxReachabilityImplWin::update);
    
    if (_hWait) {
		UnregisterWaitEx(_hWait, INVALID_HANDLE_VALUE);
	}

    if (_overlapped.hEvent) {
		CloseHandle(_overlapped.hEvent);
	}
}

//--------------------------------------------------------------
void CALLBACK ofxReachabilityImplWin::OnChange(PVOID lpParameter, BOOLEAN)
{
	ofxReachabilityImplWin *self = reinterpret_cast<ofxReachabilityImplWin *>(lpParameter);
	self->checkIPAddress();
}

//--------------------------------------------------------------
void ofxReachabilityImplWin::StartStopService(BOOL fStart)
{
	SC_HANDLE sc;
	sc = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT | SC_MANAGER_ENUMERATE_SERVICE);
	if (sc) {
		SC_HANDLE scWzcsvc = OpenService(sc, TEXT("wzcsvc"), fStart ? SERVICE_START : SERVICE_STOP | SERVICE_QUERY_STATUS);
		if (scWzcsvc) {
			if (fStart) StartService(scWzcsvc, 0, NULL);
			else        StopService(scWzcsvc);
			CloseServiceHandle(scWzcsvc);
		}
		CloseServiceHandle(sc);
	}
}

//--------------------------------------------------------------
void ofxReachabilityImplWin::StopService(SC_HANDLE sc)
{
	SERVICE_STATUS ss;

	if (QueryServiceStatus(sc, &ss) && ss.dwCurrentState != SERVICE_STOPPED && ss.dwCurrentState != SERVICE_STOP_PENDING) {
		ControlService(sc, SERVICE_CONTROL_STOP, &ss);
	}
}

//--------------------------------------------------------------
void ofxReachabilityImplWin::checkIPAddress()
{
	ULONG ulSize = 0;
	if (GetIpAddrTable(NULL, &ulSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
		PMIB_IPADDRTABLE piat = reinterpret_cast<PMIB_IPADDRTABLE>(LocalAlloc(LMEM_FIXED, ulSize));
		if (piat) {
			if (GetIpAddrTable(piat, &ulSize, 0) == ERROR_SUCCESS) {
				BOOL fFound = FALSE;
				for (DWORD dwIndex = 0; dwIndex < piat->dwNumEntries; dwIndex++) {
					PMIB_IPADDRROW prow = &piat->table[dwIndex];
					if (prow->dwAddr == 0) {
						continue;
					}
#if (OF_VERSION_MAJOR == 0 && OF_VERSION_MINOR <= 9)
					if ((prow->unused2 & (MIB_IPADDR_DYNAMIC | MIB_IPADDR_DELETED | MIB_IPADDR_DISCONNECTED)) != MIB_IPADDR_DYNAMIC) {
#else
					if ((prow->wType & (MIB_IPADDR_DYNAMIC | MIB_IPADDR_DELETED | MIB_IPADDR_DISCONNECTED)) != MIB_IPADDR_DYNAMIC) {
#endif
						continue;
					}
					fFound = TRUE;
					break;
				}
				_bConnectedTest = fFound;
				StartStopService(!fFound);
			}
			LocalFree(piat);
		}
	}

	HANDLE h;
	NotifyAddrChange(&h, &_overlapped);
}

//--------------------------------------------------------------
void ofxReachabilityImplWin::update(ofEventArgs& args)
{
    if (_bConnected && !_bConnectedTest) {
        _bConnected = false;
        ofNotifyEvent(ofxReachability::disconnectedEvent);
    }
    else if (!_bConnected && _bConnectedTest) {
        _bConnected = true;
        ofNotifyEvent(ofxReachability::connectedEvent);
    }
}
