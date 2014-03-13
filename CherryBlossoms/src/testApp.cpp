#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	// setup fluid stuff
	fluidSolver.setup(100, 100);
    fluidSolver.enableRGB(true).setFadeSpeed(0.002).setDeltaT(0.5).setVisc(0.00015).setColorDiffusion(0);
	fluidDrawer.setup(&fluidSolver);
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
	
#ifdef USE_GUI 
	gui.addSlider("fluidCellsX", fluidCellsX, 20, 400);
	gui.addButton("resizeFluid", resizeFluid);
    gui.addSlider("colorMult", colorMult, 0, 100);
    gui.addSlider("velocityMult", velocityMult, 0, 100);
	gui.addSlider("fs.viscocity", fluidSolver.viscocity, 0.0, 0.01);
	gui.addSlider("fs.colorDiffusion", fluidSolver.colorDiffusion, 0.0, 0.0003); 
	gui.addSlider("fs.fadeSpeed", fluidSolver.fadeSpeed, 0.0, 0.1); 
	gui.addSlider("fs.solverIterations", fluidSolver.solverIterations, 1, 50); 
	gui.addSlider("fs.deltaT", fluidSolver.deltaT, 0.1, 5);
	gui.addComboBox("fd.drawMode", (int&)fluidDrawer.drawMode, msa::fluid::getDrawModeTitles());
	gui.addToggle("fs.doRGB", fluidSolver.doRGB); 
	gui.addToggle("fs.doVorticityConfinement", fluidSolver.doVorticityConfinement); 
	gui.addToggle("drawFluid", drawFluid);
	gui.addToggle("fs.wrapX", fluidSolver.wrap_x);
	gui.addToggle("fs.wrapY", fluidSolver.wrap_y);
//    gui.addSlider("tuioXScaler", tuioXScaler, 0, 2);
//    gui.addSlider("tuioYScaler", tuioYScaler, 0, 2);
    
	gui.currentPage().setXMLName("ofxMSAFluidSettings.xml");
    gui.loadFromXML();
	gui.setDefaultKeys(true);
	gui.setAutoSave(true);
//    gui.show();
#endif
	
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


/*
 void testApp::draw()
 {
 //	if(drawFluid)
 //    {
 //        ofClear(255,255,0);
 //		glColor3f(1, 1, 1);
 //		fluidDrawer.draw(0, 0, ofGetWidth(), ofGetHeight());
 //	} else
 //    {
 ////		if(ofGetFrameNum()%5==0)
 //            fadeToColor(1,1, 0, 0.01);
 //	}
 ofBackground(0,0,0);
 
 //    particleSystem.updateAndDraw(fluidSolver, ofGetWindowSize(), drawFluid);
 mFlowerParticles.draw();
 //	ofDrawBitmapString(sz, 50, 50);
 
 #ifdef USE_GUI
 gui.draw();
 #endif
 //    mOpticalFlowGenerator.draw();
 }
 */

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
            ofVec2f vel = vects[j][i];
            float speed = vel.x * vel.x  + vel.y * vel.y * msa::getWindowAspectRatio() * msa::getWindowAspectRatio();    // balance the x and y components of speed with the screen aspect ratio
            if(speed > 0)
            {
                pos.x = ofClamp(pos.x, 0.0f, 1.0f);
                pos.y = ofClamp(pos.y, 0.0f, 1.0f);
//                pos.x = 1- pos.x;
                int index = fluidSolver.getIndexForPos(pos);
                
                fluidSolver.addForceAtIndex(index, vel * velocityMult);
            }
        }
    }
}

