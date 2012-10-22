#include "particle.h"

Particle::Particle(){
    //set the initial color
    color.set(ofRandom(255), ofRandom(255), ofRandom(255));
    
    //find out if vector makes things puke
    v1 = ofVec2f(5, 5);
    v2 = ofVec2f(5, 5);
    xPos = ofGetWindowWidth() * 0.5;
    yPos = ofGetWindowHeight() * 0.5;
    
}

void Particle::update(int _xDest, int _yDest){
    //update the position using vector math in notes

}

void Particle::draw(){
    ofSetColor(color);
    ofFill();
    ofCircle( xPos, yPos, 30);
}