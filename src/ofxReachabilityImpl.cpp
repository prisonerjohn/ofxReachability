//
//  ofxReachabilityImpl.cpp
//  ofxReachability
//
//  Created by Elias Zananiri on 2015-07-02.
//
//

#include "ofxReachabilityImpl.h"

//--------------------------------------------------------------
ofxReachabilityImpl::ofxReachabilityImpl()
: _bConnected(false)
{
    
}

//--------------------------------------------------------------
ofxReachabilityImpl::~ofxReachabilityImpl()
{
    
}

//--------------------------------------------------------------
bool ofxReachabilityImpl::isConnected() const
{
    return _bConnected;
}
