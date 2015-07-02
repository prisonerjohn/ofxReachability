//
//  ofxReachabilityImplPing.cpp
//  ofxReachability
//
//  Created by Elias Zananiri on 2015-07-02.
//
//

#include "ofxReachabilityImplPing.h"
#include "ofxReachability.h"

//--------------------------------------------------------------
ofxReachabilityImplPing::ofxReachabilityImplPing()
: ofThread()
, ofxReachabilityImpl()
, _pingAddress("www.google.com")
, _pingDelay(1000)
, _bConnectedTest(false)
{
    
}

//--------------------------------------------------------------
ofxReachabilityImplPing::~ofxReachabilityImplPing()
{

}

//--------------------------------------------------------------
void ofxReachabilityImplPing::setup()
{
    startThread();
    
    ofAddListener(ofEvents().update, this, &ofxReachabilityImplPing::update);
}

//--------------------------------------------------------------
void ofxReachabilityImplPing::exit()
{
    ofRemoveListener(ofEvents().update, this, &ofxReachabilityImplPing::update);
    
    waitForThread();
}

//--------------------------------------------------------------
void ofxReachabilityImplPing::update(ofEventArgs& args)
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

//--------------------------------------------------------------
void ofxReachabilityImplPing::threadedFunction()
{
    while (isThreadRunning()) {
        if (system(("ping -q -c5 " + _pingAddress + " > /dev/null 2>&1").c_str())) {
            _bConnectedTest = false;
        }
        else {
            _bConnectedTest = true;
        }
        
        sleep(_pingDelay);
    }
}

//--------------------------------------------------------------
void ofxReachabilityImplPing::setPingAddress(const string& pingAddress)
{
    _pingAddress = pingAddress;
}

//--------------------------------------------------------------
const string& ofxReachabilityImplPing::getPingAddress() const
{
    return _pingAddress;
}

//--------------------------------------------------------------
void ofxReachabilityImplPing::setPingDelay(int pingDelay)
{
    _pingDelay = pingDelay;
}

//--------------------------------------------------------------
int ofxReachabilityImplPing::getPingDelay() const
{
    return _pingDelay;
}
