#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	// setup fluid stuff
	fluidSolver.setup(100, 100);
//    fluidSolver.enableRGB(true).setFadeSpeed(0.002).setDeltaT(0.5).setVisc(0.00015).setColorDiffusion(0);
//	fluidDrawer.setup(&fluidSolver);
	fluidCellsX			= 150;
	
	drawFluid			= true;
    ofLog(OF_LOG_NOTICE, "loading the images...");
//    mTreeMask.loadImage("backgroundImages/1080/tree_nodes.png");
    
    ofEnableAlphaBlending();
    mShowHex=mShowGround=mShowFuji=mShowTree=true;
    mTree.loadImage("backgroundImages/1080/tree_.png");
    mFuji.loadImage("backgroundImages/1080/mtn.png");
    mGround.loadImage("backgroundImages/1080/land.png");
    mHex.loadImage("backgroundImages/1080/hex.png");
    
    float wxh[2]={ofGetScreenWidth(),ofGetScreenHeight()};
    
    mRect.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mRect.addVertex(ofVec3f(0,0,0));
    mRect.addTexCoord(ofVec2f(0,0));
    
    mRect.addVertex(ofVec3f(0,wxh[1],0));
    mRect.addTexCoord(ofVec2f(0,1));
    
    mRect.addVertex(ofVec3f(wxh[0],0,0));
    mRect.addTexCoord(ofVec2f(1,0));
    
    mRect.addVertex(ofVec3f(wxh[0],wxh[1],0));
    mRect.addTexCoord(ofVec2f(1,1));
    
    ofLog(OF_LOG_NOTICE, "...images loaded");
    
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    velocityMult = 1;
	
    mShowFPS = false;
	
	windowResized(ofGetWidth(), ofGetHeight());		// force this at start (cos I don't think it is called)
	pMouse = msa::getWindowCenter();
	resizeFluid			= true;
	
	ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);
}


/*
 void testApp::update()
 {
 mFlowerParticles.update(fluidSolver);
 mOpticalFlowGenerator.update();
 addForceFromOpticalFlow();
 
 
 if(resizeFluid)
 {
 fluidSolver.setSize(fluidCellsX, fluidCellsX / msa::getWindowAspectRatio());
 fluidDrawer.setup(&fluidSolver);
 resizeFluid = false;
 }
 fluidSolver.update();
 }
 */


void testApp::update()
{
    mFlowerParticles.update(fluidSolver);
    mCloudParticles.update();
    
    ///
    
    mOpticalFlowGenerator.update();
    addForceFromOpticalFlow();
    
    
    if(resizeFluid)
    {
        fluidSolver.setSize(fluidCellsX, fluidCellsX / msa::getWindowAspectRatio());
        fluidDrawer.setup(&fluidSolver);
        resizeFluid = false;
    }
    fluidSolver.update();

}


void testApp::draw()
{
    ofBackground(200,200,225);
    ofEnableAlphaBlending();
    ofEnableNormalizedTexCoords();
    
    ofPushMatrix();
    

//    ofTranslate(ofGetMouseX(),
//                ofGetMouseY(),
//                0);
    
    ofPushMatrix();

    ofTranslate(0,0,500);
    mCloudParticles.draw();
    ofPopMatrix();
    
    if(mShowFuji)
    {
        ofPushMatrix();
        ofSetColor(255,255,255,255);
        mFuji.bind();
        mRect.draw();
        mFuji.unbind();
        ofPopMatrix();
    }
    if(mShowHex)
    {
        ofTranslate(0,0,10);
        ofPushMatrix();
        ofSetColor(255,255,255,100);
        mHex.bind();
        mRect.draw();
        mHex.unbind();
        ofPopMatrix();
    }
    if(mShowGround)
    {
        ofTranslate(0,0,10);
        ofPushMatrix();
        ofSetColor(255,255,255,255);
        mGround.bind();
        mRect.draw();
        mGround.unbind();
        ofPopMatrix();
    }

    mFlowerParticles.draw(5,500);

    if(mShowTree)
    {
        ofTranslate(0,0,10);
        ofPushMatrix();
        ofSetColor(255,255,255,255);
        mTree.bind();
        mRect.draw();
        mTree.unbind();
        ofPopMatrix();
    }

    mFlowerParticles.draw(-500, 5);

    ofTranslate(0,0,10);
//    mOpticalFlowGenerator.draw();
    ofPopMatrix();
    if(mShowFPS)
    {
        stringstream s;
        s <<"FPS: " << ofGetFrameRate();
        string flowerStats = s.str();
        ofDrawBitmapString(flowerStats, 50,50);
    }
}


void testApp::keyPressed  (int key)
{
    switch(key)
    {
		case 'f':
			ofToggleFullscreen();
			break;
        
        case '1':
            mShowHex = !mShowHex;
			break;
        case '2':
            mShowGround = !mShowGround;
			break;
        case '3':
            mShowFuji = !mShowFuji;
			break;
        case '4':
            mShowTree = !mShowTree;
			break;
        case 'w':
            mFlowerParticles.mUseTextures = !mFlowerParticles.mUseTextures;
			break;
        case 'q':
            mFlowerParticles.mShowFlowerStats = !mFlowerParticles.mShowFlowerStats;
			break;
        case 'r':
            mShowFPS = !mShowFPS;
			break;
        default:
            break;
    }
}


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
	ofVec2f eventPos = ofVec2f(x, y);
	ofVec2f mouseNorm = ofVec2f(eventPos) / ofGetWindowSize();
	ofVec2f mouseVel = ofVec2f(eventPos - pMouse) / ofGetWindowSize();
	addToFluid(mouseNorm, mouseVel, true, true);
	pMouse = eventPos;

}

void testApp::mouseDragged(int x, int y, int button)
{

}

//// add force and dye to fluid, and create particles
void testApp::addToFluid(ofVec2f pos, ofVec2f vel, bool addColor, bool addForce)
{
    float speed = vel.x * vel.x  + vel.y * vel.y * msa::getWindowAspectRatio() * msa::getWindowAspectRatio();    // balance the x and y components of speed with the screen aspect ratio
    if(speed > 0)
    {
		pos.x = ofClamp(pos.x, 0.0f, 1.0f);
		pos.y = ofClamp(pos.y, 0.0f, 1.0f);
		
        int index = fluidSolver.getIndexForPos(pos);
		
		
		if(addForce)
			fluidSolver.addForceAtIndex(index, vel * velocityMult);
    }
}



void testApp::addForceFromOpticalFlow()
{
    bool addColor = true;
    bool addForce = true;

    
    ofVec2f** vects = mOpticalFlowGenerator.getFlowVectors();
    ofVec2f flowDimensions = mOpticalFlowGenerator.getWHVector();
    for(int i = 0; i < flowDimensions.x; i++)
    {
        for(int j = 0; j < flowDimensions.y; j++)
        {
            ofVec2f pos = ofVec2f(i,j);
            pos += ofVec2f(ofRandom(1),ofRandom(1));
            pos /= flowDimensions;
            ofVec2f vel = vects[j][(int)(flowDimensions.x-i-1)];
            float speed = vel.x * vel.x  + vel.y * vel.y * msa::getWindowAspectRatio() * msa::getWindowAspectRatio();    // balance the x and y components of speed with the screen aspect ratio
            if(speed > 0)
            {
                pos.x = ofClamp(pos.x, 0.0f, 1.0f);
                pos.y = ofClamp(pos.y, 0.0f, 1.0f);
//                pos.x = 1- pos.x;
                int index = fluidSolver.getIndexForPos(pos);
                vel.x*=-1;
                fluidSolver.addForceAtIndex(index, vel * velocityMult);
            }
        }
    }
}

