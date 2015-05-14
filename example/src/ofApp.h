#pragma once

#include "ofMain.h"
#include "ofxAvailability.h"

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
    ofxAvailability availability;
};
