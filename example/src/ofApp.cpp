#include "ofApp.h"
#include "ofxAvailability.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(true);
    ofBackground(ofColor::black);
    
    availability.setup();
    ofAddListener(ofxAvailability::disconnectedEvent, this, &ofApp::onDisconnected);
    ofAddListener(ofxAvailability::connectedEvent, this, &ofApp::onConnected);
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(255);
    if (availability.isConnected()) {
        ofDrawBitmapString("CONNECTED!", 10, 20);
    }
    else {
        ofDrawBitmapString("DISCONNECTED!", 10, 20);
    }
}

//--------------------------------------------------------------
void ofApp::onDisconnected()
{
    ofLogNotice("ofApp::onDisconnected");
}

//--------------------------------------------------------------
void ofApp::onConnected()
{
    ofLogNotice("ofApp::onConnected");
}
