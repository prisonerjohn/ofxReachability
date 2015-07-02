//
//  ofxReachability.h
//  ofxReachability
//
//  Created by Elie Zananiri on 2015-05-14.
//
//

#pragma once

#if defined( __WIN32__ ) || defined( _WIN32 )
    #define OFX_REACHABILITY_WIN32
#elif defined( __APPLE_CC__)
    #define OFX_REACHABILITY_APPLE
#endif

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
