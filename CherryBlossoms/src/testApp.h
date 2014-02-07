#pragma once

#include "ofMain.h"
#include "FlowerParticleSystem.h"

class testApp : public ofBaseApp
{
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

    ofVboMesh mRect;
    ofImage mTree;
    ofImage mFuji;
    ofImage mGround;
    ofImage mHex;
};



