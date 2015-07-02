//
//  ofxReachabilityImplPing.h
//  ofxReachability
//
//  Created by Elias Zananiri on 2015-07-02.
//
//

#pragma once

#include "ofMain.h"
#include "ofxReachabilityImpl.h"

class ofxReachabilityImplPing
: public ofThread
, public ofxReachabilityImpl
{
public:
    ofxReachabilityImplPing();
    ~ofxReachabilityImplPing();
    
    virtual void setup();
    virtual void exit();
    
    void setPingAddress(const string& pingAddress);
    const string& getPingAddress() const;
    
    void setPingDelay(int pingDelay);
    int getPingDelay() const;
    
protected:
    void threadedFunction();
    
private:
    string _pingAddress;
    int _pingDelay;
};
