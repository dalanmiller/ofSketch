#include "testApp.h"
#include <math.h>
const int PARTICLE_COUNT = 555;
Particle particles[PARTICLE_COUNT];


//--------------------------------------------------------------
void testApp::setup(){
    count = 55;
    total = 0;
    ORIGIN.set(200, 600);
    radius = 150;
    layer = 0;

    blowingAway = false;
    ofSetBackgroundAuto(false);

    ofBackground(0,0,0);
    ofEnableAlphaBlending();
    //ofSetFrameRate(60);

    while(total < PARTICLE_COUNT){
        for(radius = 150; radius > 0; radius -=10){
            layer++;

            for(int i = 0; i < count; i++){
                 particles[total] = Particle(radius * sin(i*2*PI/count)+ORIGIN.x, radius*cos(i*2*PI/count)+ORIGIN.y, 1000, 600);
                total++;
            }
            count *= 0.95;
        }
    }
}

//--------------------------------------------------------------
void testApp::update(){
    if(blowingAway){
       for(int i= 0; i < PARTICLE_COUNT; i++){
            particles[i].blowAway(0.3);
        }
    }
    if(comingBack){
        for(int i= 0; i < PARTICLE_COUNT; i++){
            particles[i].comeBack();
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    //background with alpha transparency
    ofSetColor(211,211,211,50);
    ofRect(0,0,ofGetWidth(),ofGetHeight());

    for(int i= 0; i < PARTICLE_COUNT; i++){
        particles[i].display();
    }
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
