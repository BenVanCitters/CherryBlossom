#pragma once



#include "ofMain.h"
#include "FlowerParticleSystem.h"

// comment this line out if you don't wanna use TUIO
// you will need ofxTUIO & ofxOsc
//#define USE_TUIO		

// comment this line out if you don't wanna use the GUI
// you will need ofxSimpleGuiToo, ofxMSAInteractiveObject & ofxXmlSettings
// if you don't use the GUI, you won't be able to see the fluid parameters
//#define USE_GUI		

#ifdef USE_GUI 
#include "ofxSimpleGuiToo.h"
#endif

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
    
    float                   colorMult;
    float                   velocityMult;

    FlowerParticleSystem    mFlowerParticles;
	ofVec2f                 pMouse;
};



