//
//  ofxReachability.cpp
//  ofxReachability
//
//  Created by Elie Zananiri on 2015-05-14.
//
//

#include "ofxReachability.h"

//--------------------------------------------------------------
ofEvent<void> ofxReachability::disconnectedEvent;
ofEvent<void> ofxReachability::connectedEvent;

//--------------------------------------------------------------
ofxReachability::ofxReachability()
: ofThread()
, _bConnected(false)
, _pingAddress("www.google.com")
, _pingDelay(1000)
{
    
}

//--------------------------------------------------------------
ofxReachability::~ofxReachability()
{
    exit();
}

//--------------------------------------------------------------
void ofxReachability::setup()
{
    startThread();
}

//--------------------------------------------------------------
void ofxReachability::exit()
{
    waitForThread();
}

//--------------------------------------------------------------
void ofxReachability::threadedFunction()
{
    while (isThreadRunning()) {
        if (system(("ping -q -c5 " + _pingAddress + " > /dev/null 2>&1").c_str())) {
            // Not connected.
            if (_bConnected) {
                _bConnected = false;
                ofNotifyEvent(ofxReachability::disconnectedEvent);
            }
        }
        else {
            // Connected.
            if (!_bConnected) {
                _bConnected = true;
                ofNotifyEvent(ofxReachability::connectedEvent);
            }
        }
    
        sleep(_pingDelay);
    }
}

//--------------------------------------------------------------
bool ofxReachability::isConnected() const
{
    return _bConnected;
}

//--------------------------------------------------------------
void ofxReachability::setPingAddress(const string& pingAddress)
{
    _pingAddress = pingAddress;
}

//--------------------------------------------------------------
const string& ofxReachability::getPingAddress() const
{
    return _pingAddress;
}

//--------------------------------------------------------------
void ofxReachability::setPingDelay(int pingDelay)
{
    _pingDelay = pingDelay;
}

//--------------------------------------------------------------
int ofxReachability::getPingDelay() const
{
    return _pingDelay;
}
