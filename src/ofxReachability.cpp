//
//  ofxReachability.cpp
//  ofxReachability
//
//  Created by Elie Zananiri on 2015-05-14.
//
//

#include "ofxReachability.h"

#if defined(OFX_REACHABILITY_WIN32)
	#include "ofxReachabilityImplWin.h"
#elif defined(OFX_REACHABILITY_APPLE)
    #include "ofxReachabilityImplApple.h"
#else
    #include "ofxReachabilityImplPing.h"
#endif

//--------------------------------------------------------------
ofEvent<void> ofxReachability::disconnectedEvent;
ofEvent<void> ofxReachability::connectedEvent;

//--------------------------------------------------------------
ofxReachability::ofxReachability()
: _impl(NULL)
{
#if defined(OFX_REACHABILITY_WIN32)
    _impl = new ofxReachabilityImplWin();
#elif defined(OFX_REACHABILITY_APPLE)
    _impl = new ofxReachabilityImplApple();
#else
    _impl = new ofxReachabilityImplPing();
#endif
}

//--------------------------------------------------------------
ofxReachability::~ofxReachability()
{
    exit();
    
    delete _impl;
    _impl = NULL;
}

//--------------------------------------------------------------
void ofxReachability::setup()
{
    _impl->setup();
}

//--------------------------------------------------------------
void ofxReachability::exit()
{
    _impl->exit();
}

//--------------------------------------------------------------
bool ofxReachability::isConnected() const
{
    return _impl->isConnected();
}

//--------------------------------------------------------------
ofxReachabilityImpl * ofxReachability::getImpl()
{
    return _impl;
}
