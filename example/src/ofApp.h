#pragma once

#include "ofMain.h"
#include "ofxReachability.h"

class ofApp
: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    
    void onDisconnected();
    void onConnected();
    
private:
    ofxReachability reachability;
};
