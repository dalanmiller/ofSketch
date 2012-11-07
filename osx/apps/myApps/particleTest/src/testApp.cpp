#include "testApp.h"
#include <math.h>
const int PARTICLE_COUNT = 555;
Particle particles[PARTICLE_COUNT];


//--------------------------------------------------------------
void testApp::setup(){
    //--- BEGIN PARTICLE SETUP --//
    count = 55;
    total = 0;
    ORIGIN.set(200, 600);
    radius = 150;
    layer = 0;

    blowingAway = false;
    ofSetBackgroundAuto(false);
    //ofBackground(0,0,0);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);

    while(total < PARTICLE_COUNT){
        for(radius = 150; radius > 0; radius -=10){
            layer++;

            for(int i = 0; i < count; i++){
                 particles[total] = Particle(radius * sin(i*2*PI/count)+ORIGIN.x, radius*cos(i*2*PI/count)+ORIGIN.y, 1100, 600);
                total++;
            }
            count *= 0.95;
        }
    }
    //-- END PARTICLE SETUP--//
    futuraMedium.loadFont("Futura.ttc", 12);
    
    // Twitter API: http://dev.twitter.com/doc/get/trends/current
	string url = "http://search.twitter.com/search.json?q=%23cobra&src=typd";
    // Now parse the JSON
	bool parsingSuccessful = result.open(url);
	if ( parsingSuccessful )
    {
		cout << result.getRawString() << endl;
		
	}
    else
    {
		cout  << "Failed to parse JSON" << endl;
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
    ofSetColor(175,27,244,50);
    ofRect(0,0,ofGetWidth(),ofGetHeight());

    for(int i= 0; i < PARTICLE_COUNT; i++){
        particles[i].display();
    }
    
    //--TWITTER TEST --//
    ofSetHexColor(0x000000);
    
    ofxJSONElement text = result["results"];
    //for(int i=0; i < text.size(); i++)
    for(int i=0; i < 5; i++)
	{
		string message = text[i]["text"].asString();
		futuraMedium.drawString(message, 10, 40*i+40);
	}
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 98){//'b'
        blowingAway = true;
        comingBack = false;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key == 98){//'b'
        comingBack = true;
        blowingAway = false;
    }
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
