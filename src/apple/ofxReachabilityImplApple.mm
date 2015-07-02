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
struct ReachabilityWrapper
{
    Reachability * reachability;
};

//--------------------------------------------------------------
ofxReachabilityImplApple::ofxReachabilityImplApple()
: ofxReachabilityImpl()
, _wrapper(new ReachabilityWrapper)
{
    _wrapper->reachability = [Reachability reachabilityForInternetConnection];
}

//--------------------------------------------------------------
ofxReachabilityImplApple::~ofxReachabilityImplApple()
{
    if (_wrapper) {
        [_wrapper->reachability release];
    }
    delete _wrapper;
}

//--------------------------------------------------------------
void ofxReachabilityImplApple::setup()
{
    _bConnected = _wrapper->reachability.isReachable;
    
    _wrapper->reachability.reachableBlock = ^(Reachability * reachability) {
        dispatch_async(dispatch_get_main_queue(), ^{
            _bConnected = true;
            ofNotifyEvent(ofxReachability::connectedEvent);
        });
    };
    
    _wrapper->reachability.unreachableBlock = ^(Reachability * reachability) {
        dispatch_async(dispatch_get_main_queue(), ^{
            _bConnected = false;
            ofNotifyEvent(ofxReachability::disconnectedEvent);
        });
    };
    
    [_wrapper->reachability startNotifier];
}

//--------------------------------------------------------------
void ofxReachabilityImplApple::exit()
{
    [_wrapper->reachability stopNotifier];
    
    _wrapper->reachability.reachableBlock = nil;
    _wrapper->reachability.unreachableBlock = nil;
}
