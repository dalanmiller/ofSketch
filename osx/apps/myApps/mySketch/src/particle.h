#ifndef particle_h
#define particle_h

#include "ofMain.h"

class Particle{

    public:
    //constructor
    Particle();
    
    ofColor color;
    
    
    void update(int _xDest, int _yDest);
    void draw();
    

    private:
    ofVec2f v1; 
    ofVec2f v2;
    int xPos; //placeHolder to display object
    int yPos; //place holder to display object
};

#endif