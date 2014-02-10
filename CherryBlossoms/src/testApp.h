#pragma once

#include "ofMain.h"
#include "FlowerParticleSystem.h"
#include "CloudParticleSystem.h"

class testApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
    
    float colorMult;
    float velocityMult;

    FlowerParticleSystem mFlowerParticles;
    CloudParticleSystem mCloudParticles;
    ofVboMesh mRect;
    ofImage mTree;
    bool mShowTree;
    ofImage mFuji;
    bool mShowFuji;
    ofImage mGround;
    bool mShowGround;
    ofImage mHex;
    bool mShowHex;
};



