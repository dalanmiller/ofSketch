#include "particle.h"

Particle::Particle(){
    //set the initial color
    //color.set(ofRandom(255), ofRandom(255), ofRandom(255));
    color.set(255);

    location.set(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight())); //random start location
    velocity.set(0, 0);
    topspeed = ofRandom(5);
    scalar = 0.5;
    //target.set(ofGetAppPtr()->mouseX, ofGetAppPtr()->mouseY);
}

Particle::Particle(int x, int y){//pass in a point that particle should gravitate towards
    color.set(0);

    //location.set(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight())); //random start location
    location.set(1024, 0);
    velocity.set(0, 0);
    //topspeed = ofRandom(5);
    topspeed = 5;
    scalar = 0.5;
    target.set(x, y);
}

void Particle::update(){
    //contains pointer to base app variable
    ofVec2f target(this->target.x, this->target.y);
    dir = target - location;
    dir.normalize();
    dir *= scalar;
    acceleration = dir;

    velocity += acceleration;
    velocity.limit(topspeed * ofDist(location.x, location.y, target.x, target.y)/500); //creates an easing effect
    location+=velocity;
    
    std:: cout << ofDist(location.x, location.y, target.x, target.y) << std::endl;
}


void Particle::display(){
    ofSetColor(color);
    ofFill();
    ofCircle( location.x, location.y, 1);
}

