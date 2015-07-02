//
//  ofxReachabilityImpl.h
//  ofxReachability
//
//  Created by Elias Zananiri on 2015-07-02.
//
//

#pragma once

#include "ofMain.h"

class ofxReachabilityImpl
{
public:
    ofxReachabilityImpl();
    virtual ~ofxReachabilityImpl();
    
    virtual void setup() = 0;
    virtual void exit() = 0;
    
    bool isConnected() const;
    
protected:
    bool _bConnected;
};
