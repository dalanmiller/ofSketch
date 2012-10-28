#ifndef particle_h
#define particle_h

#include "ofMain.h"

class Particle{

    public:
    //constructor
    Particle();
    Particle(int x, int y);

    //methods
    void update(); //update the position of the particle
    void display(); //draw the particle

    private:
    //properties
    //vectors will be converted to 3D vectors in final phase
    ofVec2f location;
    ofVec2f velocity;
    ofVec2f acceleration;
    ofVec2f dir; //used to calculate the direction of the particle
    ofPoint target; 
    float scalar;
    float topspeed;

    ofColor color; //final particle should probably glow or something
};

#endif
