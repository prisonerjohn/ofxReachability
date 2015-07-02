#include "ofApp.h"
#include "ofxReachability.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(true);
    ofBackground(ofColor::black);
    
    reachability.setup();
    ofAddListener(ofxReachability::disconnectedEvent, this, &ofApp::onDisconnected);
    ofAddListener(ofxReachability::connectedEvent, this, &ofApp::onConnected);
}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(255);
    if (reachability.isConnected()) {
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
