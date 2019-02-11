#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    string title = "listening for osc messages on port " + ofToString(PORT);
    ofSetWindowTitle(title);

    ofSetFrameRate(60); // run at 60 fps
    ofSetVerticalSync(true);

    receiver.setup(PORT);
    gui.setup();
    gui.add(highMagnitude);
    gui.add(midMagnitude);
    gui.add(lowMagnitude);
}

//--------------------------------------------------------------
void ofApp::update(){
	// hide old messages
	for (int i = 0; i < NUM_MSG_STRINGS; i++) {
		if (timers[i] < ofGetElapsedTimef()) {
			msgStrings[i] = "";
		}
	}

	// check for waiting messages
	while(receiver.hasWaitingMessages()){

		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(m);

		// check for high
		if(m.getAddress() == "/high"){
			// all the values are floats
			high = m.getArgAsFloat(0);
		}
		// check for mid
		else if(m.getAddress() == "/mid"){
			mid = m.getArgAsFloat(0);
		}
		// check for low
		else if(m.getAddress() == "/low"){
			low = m.getArgAsFloat(0);
		}
		else{
                        string msgString;
                        msgString = m.getAddress();
                        ofLog() << "address "+ msgString+ " not identified";
		}
                collectMessage(m);
	}
}

void ofApp::collectMessage(ofxOscMessage m){
    string msgString;
    msgString = m.getAddress();
    msgString += ":";
    for(size_t i = 0; i < m.getNumArgs(); i++){

        // get the argument type
        msgString += " ";
        msgString += m.getArgTypeName(i);
        msgString += ":";

        // display the argument - make sure we get the right type
        if(m.getArgType(i) == OFXOSC_TYPE_INT32){
            msgString += ofToString(m.getArgAsInt32(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
            msgString += ofToString(m.getArgAsFloat(i));
        }
        else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
            msgString += m.getArgAsString(i);
        }
        else{
            msgString += "unhandled argument type " + m.getArgTypeName(i);
        }
    }

    // add to the list of strings to display
    msgStrings[currentMsgString] = msgString;
    timers[currentMsgString] = ofGetElapsedTimef() + 5.0f;
    currentMsgString = (currentMsgString + 1) % NUM_MSG_STRINGS;
    
    // clear the next line
    msgStrings[currentMsgString] = "";
};


//--------------------------------------------------------------
void ofApp::draw(){
    ofLog() << high;
    ofLog() << low;
    ofLog() << mid;
    ofLog() << "end";

	ofBackgroundGradient(100, 0);
    auto width = ofGetWidth();
    auto height = ofGetHeight();

    auto padding = width/4.0f;

    //high
    ofPushStyle();
    ofSetColor(ofFloatColor::aqua);
    ofDrawRectangle(padding, height, 50, -high* height*highMagnitude);
    ofDrawBitmapString("high", padding-10, height);
    ofPopStyle();

    //mid
    ofPushStyle();
    ofSetColor(ofFloatColor::red);
    ofDrawRectangle(padding*2, height-10, 50, -mid* height*midMagnitude);
    ofDrawBitmapString("mid", padding*2, height);
    ofPopStyle();

    //low
    ofPushStyle();
    ofSetColor(ofFloatColor::greenYellow);
    ofDrawRectangle(padding*3, height-10, 50, -(low * height*lowMagnitude));
    ofDrawBitmapString("low", padding*3, height);
    ofPopStyle();

    // draw recent unrecognized messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
	ofDrawBitmapStringHighlight(msgStrings[i], 10, gui.getHeight()+10 + 15 * i);
    }

    gui.draw();
}


