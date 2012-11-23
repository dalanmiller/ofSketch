#include "testApp.h"

#include <math.h>

const int PARTICLE_COUNT = 555;
Particle particles[PARTICLE_COUNT];
float Force = 0.0;


//--------------------------------------------------------------
void testApp::setup(){
    //--- BEGIN PARTICLE SETUP --//
    count = 55;
    total = 0;
    ORIGIN.set(1024/2, 768/2);
    radius = 150;
    layer = 0;
    
    blowingAway = false;
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
    ofSetFrameRate(60);

    while(total < PARTICLE_COUNT){
        for(radius = 150; radius > 0; radius -=10){
            layer++;

            for(int i = 0; i < count; i++){
                 particles[total] = Particle(radius * sin(i*2*PI/count)+ORIGIN.x, radius*cos(i*2*PI/count)+ORIGIN.y, genParticleXRange(), genParticleYRange());
                total++;
            }
            count *= 0.95;
        }
    }
    //-- END PARTICLE SETUP--//
    futuraMedium.loadFont("Futura.ttc", 12);
    
	string url = "http://localhost:5000/cobra";
    // Now parse the JSON
	bool parsingSuccessful = result.open(url);
	if ( parsingSuccessful )
    {
		//cout << result.getRawString() << endl;
        cout << "Parsing successful" << endl;
		
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
            particles[i].blowAway(Force);
        }
    }
    if(comingBack){
        for(int i= 0; i < PARTICLE_COUNT; i++){
            particles[i].comeBack();
        }
    }
    
    //Timer test
    //std::cout << "Seconds Elapsed: " <<  ofGetElapsedTimef() << std::endl;;
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
    
    ofxJSONElement text = result;
    //for(int i=0; i < text.size(); i++)
    for(int i=0; i < 5; i++)
	{
		string message = text[i]["text"].asString();
		futuraMedium.drawString(message, 10, 40*i+40);
	}
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    //357 = Up
    //359 = Down
    cout << key << endl;
    if(key == 98){//'b'
        blowingAway = true;
        comingBack = false;
    }else if(key == 357){
        Force += 0.1;
    }
    else if(key == 359){
        Force -= 0.1;
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
