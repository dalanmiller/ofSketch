#pragma once

#include "ofMain.h"
#include "particle.h"
#include "ofxJSONElement.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		int count;
		int total;
		int layer;
        int radius;

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofPoint ORIGIN;
        Particle p_test;

        bool blowingAway;
        bool comingBack;
    
        ofTrueTypeFont futuraMedium;
    
        ofxJSONElement result;
};
