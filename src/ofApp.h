#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"

// listening port
#define PORT 10000

// max number of strings to display
#define NUM_MSG_STRINGS 20

// demonstrates receiving and processing OSC messages with an ofxOscReceiver,
// use in conjunction with the oscSenderExample
class ofApp : public ofBaseApp{
	public:

    void setup();
    void update();
    void draw();

private:
    void collectMessage(ofxOscMessage m);


    ofxOscReceiver receiver;
    ofxPanel gui;
    ofParameter<float> highMagnitude = {"high magn.", 5.0f, 0.0f, 50.0f};
    ofParameter<float> midMagnitude = {"mid magn.", 5.0f, 0.0f, 50.0f};
    ofParameter<float> lowMagnitude = {"low magn.", 5.0f, 0.0f, 50.0f};

    int currentMsgString;
    string msgStrings[NUM_MSG_STRINGS];
    float timers[NUM_MSG_STRINGS];

    float high = 0.0f;
    float mid = 0.0f;
    float low = 0.0f;
};
