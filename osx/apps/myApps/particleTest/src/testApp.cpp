#include "testApp.h"
#include <math.h>
#include <time.h>
#include <string> //substr

const int PARTICLE_COUNT = 555;
Particle particles[PARTICLE_COUNT];
float Force = 0.0;
float scorePercent = 0.0;
ofxJSONElement text;


//-- Timer variables --//
time_t mark = time(NULL);
time_t now;
double dif;
int previous = 0;
int recordCount;

//--------------------------------------------------------------
void testApp::setup(){
    //--- BEGIN PARTICLE SETUP --//
    count = 55;
    total = 0;
    ORIGIN.set(1024/2, 768/2);
    radius = 150;
    layer = 0;
    wishindex = 0;
    incremented = false;
    
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
    futuraMedium.loadFont("Futura.ttc", 14);
    
	string url = "http://localhost:5000/I wish";
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
    
    text = result;
    recordCount = text.size();
    
    //-- SERIAL --//
    serialVal = 0;
    serial.enumerateDevices(); //depending on what is listed
    serial.setup("tty.usbmodem1a21", 9600);
    readSerialMessage = true;
    countCycles = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    //-- SERIAL --//
    if(readSerialMessage){
        //send a handshake to the arduino serial
        serial.writeByte('a');
        if(serial.available() > 0){
            //make sure there's something to write all the data to
            unsigned char bytesReturned[NUM_BYTES];
            memset(bytesReturned, 0, NUM_BYTES); //empty the variable?
            
            //serial.readBytes(bytesReturned, NUM_BYTES);
            //keep reading bytes, until there's nothing left to read
            while(serial.readBytes(bytesReturned, NUM_BYTES) > 0){};
            string serialData = (char*) bytesReturned; // cast to string
            serialVal = ofToInt(serialData);
            cout << "Serial value  = " << serialVal << endl;
        }
        //serial.flush();
    }
    readSerialMessage = false;
    countCycles++;
    if(countCycles % 10 == 0){
        readSerialMessage = true;
    }
    
    /*
    if(serialVal > 250){
        Force = serialVal;
        blowingAway = true;
        comingBack = false;
    }else{
        comingBack = true;
        blowingAway = false;
    }*/
    
    if(blowingAway){
       for(int i= 0; i < PARTICLE_COUNT; i++){
            particles[i].blowAway(Force);
        }
    }
    if(comingBack){
        incremented = false; //flag. You can move to the next record once the particles are coming back
        for(int i= 0; i < PARTICLE_COUNT; i++){
            particles[i].comeBack();
        }
    }
    
    scorePercent = Particle::score/float(PARTICLE_COUNT);
    if(scorePercent == 1 && !incremented){
        incrementWishList();
        incremented = true;
    }
    
    //-- Timer --//
    now = time(NULL);
    dif = difftime(now, mark);
    if(dif != previous){
        previous = dif;
        if(previous % 5 ==0){
            //do something after 5 seconds have passed
        }
    }
    
    //-- Text --//
    message = text[wishindex]["text"].asString();
    if(message.length() > 70){
		//if the lengrth is over this threshold, find the last punctuation mark or space
        size_t mid_space = message.rfind(' ', 70);
		//string substr ( size_t pos = 0, size_t n = npos ) const;
		string temp = message.substr(0, mid_space);
		message2 = message.substr(mid_space+1);
        message = temp;
	}else{
        message2 = string(); //empty string
    }
}

//--------------------------------------------------------------
void testApp::draw(){

    //background with alpha transparency
    ofSetColor(175,27,244, 50);
    ofRect(0,0,ofGetWidth(),ofGetHeight());

    for(int i= 0; i < PARTICLE_COUNT; i++){
        particles[i].display();
    }
    
    //--Score Bar--//
    ofSetColor(255, 255, 255, 30);
    ofRect(0, (ofGetHeight()/2)-12.5, ofGetWidth()*scorePercent, 100);
    
    //-- Text --//
    ofSetHexColor(0xFFFFFF);
    if(message2.empty()){
        futuraMedium.drawString(message, 10, 40);
    }else{
        futuraMedium.drawString(message, 10, 40);
        futuraMedium.drawString(message2, 10, 65);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    //357 = Up
    //359 = Down
    //358 = Left
    //356 = Right
   
    switch(key){
        case(98):
            blowingAway = true;
            comingBack = false;
            break;
        case(357):
            //up
            Force += 0.1;
            //cout << "Force = " << Force << endl; //test seems like a value from 1-1.5 is desireable. Above that is ok.
            break;
        case(359):
            //down
            Force -= 0.1;
            //cout << "Force = " << Force << endl;
            break;
        case(358):
            //right
            incrementWishList();
            break;
        case(356):
            decrementWishList();
            //left
            break;
        default:
            cout << key << " was pressed " <<  endl;
    }
}

void testApp::incrementWishList(){
    wishindex++;
    wishindex %= recordCount;
}

void testApp::decrementWishList(){
    wishindex > 0? wishindex--: wishindex = recordCount; //ternary, bitches
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
