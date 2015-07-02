//
//  ofxReachability.h
//  ofxReachability
//
//  Created by Elie Zananiri on 2015-05-14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxReachabilityImpl.h"

class ofxReachability
{
public:
    ofxReachability();
    ~ofxReachability();
    
    void setup();
    void exit();
    
    bool isConnected() const;
    
    ofxReachabilityImpl * getImpl();
    
    static ofEvent<void> disconnectedEvent;
    static ofEvent<void> connectedEvent;
    
private:
    ofxReachabilityImpl * _impl;
};
