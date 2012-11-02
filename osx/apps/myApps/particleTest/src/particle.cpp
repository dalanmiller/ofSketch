#include "particle.h"
#include "testApp.h"
#include "ofMain.h"

Particle::Particle(){
    //default constructor - find out a way to get rid of this
}

Particle::Particle(int homeX, int homeY, int targetX, int targetY){
    velocity.set(0, 0);
    topspeed = int(ofRandom(3,5));
    scalar= ofRandom(2.0, 3.5); //works nicely when coming back with a value of 0.3
    home.set(homeX, homeY);
    location = home; //start at home
    target.set(targetX, targetY);
    minDist = 0.1;

    firstBlow = true;
    firstComingBack = false;
    atHome = true;
    atTarget = false;
}


void Particle::display(){
    ofSetColor(ofColor(255, 255, 255, 50));
    ofFill();
    ofCircle(location.x, location.y, 3);
    ofSetColor(ofColor(255, 255, 255, 150));
    ofFill();
    ofCircle(location.x, location.y, 2);
    ofSetColor(ofColor(255, 255, 255));
    ofFill();
    ofCircle(location.x, location.y, 1);
}

void Particle::blowAway(float force){
    //approach a target that is slightly offscreen
    if(!atTarget){
        atHome = false;
        dir = target - location;
        dir.normalize();
        dir *= force * scalar;
        acceleration = dir;

        velocity += acceleration;
        velocity.limit(topspeed * ofDist(location.x, location.y, target.x, target.y)/100); //creates an easing effect
        velocity.limit(topspeed);

        //here we want to add an initial vertical vector
        if(firstBlow){
            addInitVertVec();
            firstBlow = false;
        }

        location+=velocity;

        if(ofDist(location.x, location.y, target.x, target.y) <= minDist){
            atTarget = true;
            firstComingBack = true;
        }
    }
}

void Particle::comeBack(){
    if(!atHome){
        atTarget = false;
        //return to home position
        dir = home - location;
        dir.normalize();
        dir *= scalar;
        acceleration = dir;

        velocity += acceleration;
        velocity.limit(5 * ofDist(location.x, location.y, home.x, home.y)/100); //creates an easing effect
        velocity.limit(5);

        //here we want to add an initial vertical vector. The initial spike should exceed the maxiumum speed
        if(firstComingBack){
            addInitVertVec();
            firstComingBack = false;
        }

        location+=velocity;
        if(ofDist(location.x, location.y, home.x, home.y) <= minDist){
            atHome = true;
            firstBlow = true;
        }
    }
}

void Particle::addInitVertVec(){
    int x = ((testApp*)ofGetAppPtr())->ORIGIN.x;
    int y = ((testApp*)ofGetAppPtr())->ORIGIN.y;

    velocity.y -= 5;
    
    if(location.y - y > 0){
        velocity.y *= -1;
    }
}
