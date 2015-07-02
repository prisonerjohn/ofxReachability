//
//  ofxReachabilityImplApple.h
//  reachabilityExample
//
//  Created by Elias Zananiri on 2015-07-02.
//
//

#pragma once

#include "ofMain.h"
#include "ofxReachabilityImpl.h"

struct ReachabilityWrapper;

class ofxReachabilityImplApple
: public ofThread
, public ofxReachabilityImpl
{
public:
    ofxReachabilityImplApple();
    ~ofxReachabilityImplApple();
    
    virtual void setup();
    virtual void exit();
    
private:
    ReachabilityWrapper * _wrapper;
};

