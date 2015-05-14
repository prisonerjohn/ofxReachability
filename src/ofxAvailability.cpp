//
//  ofxAvailability.cpp
//  ofxAvailability
//
//  Created by Elie Zananiri on 2015-05-14.
//
//

#include "ofxAvailability.h"

//--------------------------------------------------------------
ofEvent<void> ofxAvailability::disconnectedEvent;
ofEvent<void> ofxAvailability::connectedEvent;

//--------------------------------------------------------------
ofxAvailability::ofxAvailability()
: ofThread()
, _bConnected(false)
, _pingAddress("www.google.com")
, _pingDelay(1000)
{
    
}

//--------------------------------------------------------------
ofxAvailability::~ofxAvailability()
{
    exit();
}

//--------------------------------------------------------------
void ofxAvailability::setup()
{
    startThread();
}

//--------------------------------------------------------------
void ofxAvailability::exit()
{
    waitForThread();
}

//--------------------------------------------------------------
void ofxAvailability::threadedFunction()
{
    while (isThreadRunning()) {
        if (system(("ping -q -c5 " + _pingAddress + " > /dev/null 2>&1").c_str())) {
            // Not connected.
            if (_bConnected) {
                _bConnected = false;
                ofNotifyEvent(ofxAvailability::disconnectedEvent);
            }
        }
        else {
            // Connected.
            if (!_bConnected) {
                _bConnected = true;
                ofNotifyEvent(ofxAvailability::connectedEvent);
            }
        }
    
        sleep(_pingDelay);
    }
}

//--------------------------------------------------------------
bool ofxAvailability::isConnected() const
{
    return _bConnected;
}

//--------------------------------------------------------------
void ofxAvailability::setPingAddress(const string& pingAddress)
{
    _pingAddress = pingAddress;
}

//--------------------------------------------------------------
const string& ofxAvailability::getPingAddress() const
{
    return _pingAddress;
}

//--------------------------------------------------------------
void ofxAvailability::setPingDelay(int pingDelay)
{
    _pingDelay = pingDelay;
}

//--------------------------------------------------------------
int ofxAvailability::getPingDelay() const
{
    return _pingDelay;
}
