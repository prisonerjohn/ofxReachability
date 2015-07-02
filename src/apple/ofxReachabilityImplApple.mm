//
//  ofxReachabilityImplApple.cpp
//  reachabilityExample
//
//  Created by Elias Zananiri on 2015-07-02.
//
//

#include "ofxReachabilityImplApple.h"
#include "ofxReachability.h"

#import "Reachability.h"

//--------------------------------------------------------------
ofxReachabilityImplApple::ofxReachabilityImplApple()
: ofxReachabilityImpl()
{
    _reach = [Reachability reachabilityForInternetConnection];
}

//--------------------------------------------------------------
ofxReachabilityImplApple::~ofxReachabilityImplApple()
{
    [_reach release];
}

//--------------------------------------------------------------
void ofxReachabilityImplApple::setup()
{
    _bConnected = _reach.isReachable;
    
    _reach.reachableBlock = ^(Reachability * reachability) {
        dispatch_async(dispatch_get_main_queue(), ^{
            _bConnected = true;
            ofNotifyEvent(ofxReachability::connectedEvent);
        });
    };
    
    _reach.unreachableBlock = ^(Reachability * reachability) {
        dispatch_async(dispatch_get_main_queue(), ^{
            _bConnected = false;
            ofNotifyEvent(ofxReachability::disconnectedEvent);
        });
    };
    
    [_reach startNotifier];
}

//--------------------------------------------------------------
void ofxReachabilityImplApple::exit()
{
    [_reach stopNotifier];
    
    _reach.reachableBlock = nil;
    _reach.unreachableBlock = nil;
}
