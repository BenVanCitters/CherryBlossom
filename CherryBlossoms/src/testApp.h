#pragma once

#include "MSAFluid.h"
#include "ofMain.h"
#include "OpticalFlowGenerator.h"
#include "FlowerParticleSystem.h"
#include "CloudParticleSystem.h"


// comment this line out if you don't wanna use the GUI
// you will need ofxSimpleGuiToo, ofxMSAInteractiveObject & ofxXmlSettings
// if you don't use the GUI, you won't be able to see the fluid parameters
//#define USE_GUI

#ifdef USE_GUI 
#include "ofxSimpleGuiToo.h"
#endif
class testApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void fadeToColor(float r, float g, float b, float speed);
	void addToFluid(ofVec2f pos, ofVec2f vel, bool addColor, bool addForce);

    void addForceFromOpticalFlow();
    
    //video stuff
    OpticalFlowGenerator mOpticalFlowGenerator;
    
    
    float                   colorMult;
    float                   velocityMult;
	int                     fluidCellsX;
	bool                    resizeFluid;
	bool                    drawFluid;
//	bool                    drawParticles;
	
	msa::fluid::Solver      fluidSolver;
	msa::fluid::DrawerGl	fluidDrawer;
	
	ofVec2f                 pMouse;

    
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
    bool mShowFPS;
};



