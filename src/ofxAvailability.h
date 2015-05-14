//
//  ofxAvailability.h
//  ofxAvailability
//
//  Created by Elie Zananiri on 2015-05-14.
//
//

#pragma once

#include "ofMain.h"

class ofxAvailability
: ofThread
{
public:
    ofxAvailability();
    ~ofxAvailability();
    
    void setup();
    void exit();
    
    bool isConnected() const;
    
    void setPingAddress(const string& pingAddress);
    const string& getPingAddress() const;
    
    void setPingDelay(int pingDelay);
    int getPingDelay() const;
    
    static ofEvent<void> disconnectedEvent;
    static ofEvent<void> connectedEvent;
    
protected:
    void threadedFunction();
    
private:
    bool _bConnected;
    string _pingAddress;
    int _pingDelay;
};
