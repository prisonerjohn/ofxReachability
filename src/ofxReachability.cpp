//
//  ofxReachability.cpp
//  ofxReachability
//
//  Created by Elie Zananiri on 2015-05-14.
//
//

#include "ofxReachability.h"

#if defined(OFX_REACHABILITY_APPLE)

#elif defined(OFX_REACHABILITY_WIN32)

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
#if defined(OFX_REACHABILITY_APPLE)
    
#elif defined(OFX_REACHABILITY_WIN32)
    
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
