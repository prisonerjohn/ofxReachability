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

#include <objc/objc-runtime.h>

#ifdef __OBJC__
@class Reachability;
#else
typedef struct objc_object Reachability;
#endif

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
    Reachability * _reach;
};

