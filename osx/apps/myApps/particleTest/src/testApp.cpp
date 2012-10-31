#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ORIGIN.set(100, 600);
    p_test = Particle(50, 600, 1000, 600); //homeX, homeY, targetX, targetY
    blowingAway = false;
    
    ofSetBackgroundAuto(false);
    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void testApp::update(){
    if(blowingAway){
        p_test.blowAway(0.3);
    }
    if(comingBack){
        p_test.comeBack();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //background with alpha transparency
    ofSetColor(211,211,211,50);
    ofRect(0,0,ofGetWidth(),ofGetHeight());

    //placeholder
    ofSetColor(ofColor::white);
    ofFill();
    ofCircle(ORIGIN.x, ORIGIN.y, 50);
    
    
    //"particle"
    
    p_test.display();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 98){//'b'
        blowingAway = true;
        comingBack = false;
    }
    if(key == 99){//'c'
        comingBack = true;
        blowingAway = false;
    }      
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}