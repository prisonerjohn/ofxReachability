//
//  ofxReachabilityImplWin.h
//  ofxReachability
//
//  Created by Elias Zananiri on 2015-07-02.
//  Based on http://blogs.msdn.com/b/oldnewthing/archive/2010/04/19/9998139.aspx
//

#pragma once

#include "ofMain.h"
#include "ofxReachabilityImpl.h"

class ofxReachabilityImplWin
: public ofThread
, public ofxReachabilityImpl
{
public:
    ofxReachabilityImplWin();
    ~ofxReachabilityImplWin();
    
    virtual void setup();
    virtual void exit();
    
    void update(ofEventArgs& args);
    
protected:
    static void CALLBACK OnChange(PVOID lpParameter, BOOLEAN);
    static void StartStopService(BOOL fStart);
	static void StopService(SC_HANDLE sc);

	void checkIPAddress();

private:
    HANDLE _hWait;
    OVERLAPPED _overlapped;
	bool _bConnectedTest;
};
