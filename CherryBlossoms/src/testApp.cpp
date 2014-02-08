#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofLog(OF_LOG_NOTICE, "loading the images...");
//    mTreeMask.loadImage("backgroundImages/1080/tree_nodes.png");

	mTree.loadImage("backgroundImages/1080/tree_.png");
    mFuji.loadImage("backgroundImages/1080/mtn.png");
    mGround.loadImage("backgroundImages/1080/land.png");
    mHex.loadImage("backgroundImages/1080/hex_alpha_grad.png");
    
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

//	windowResized(ofGetWidth(), ofGetHeight());		// force this at start (cos I don't think it is called)
	
//	ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);
}


void testApp::update()
{
    mFlowerParticles.update();
}

void testApp::draw()
{
    ofBackground(0,0,0);
//    ofEnableAlphaBlending();
//    ofEnableNormalizedTexCoords();
    
    ofPushMatrix();
    

//    ofTranslate(ofGetMouseX(),
//                ofGetMouseY(),
//                0);
    ofPushMatrix();
//    ofSetColor(255,255,255,255);
//    mFuji.bind();
//    mRect.draw();
//    mFuji.unbind();
    ofPopMatrix();
    
    ofTranslate(0,0,10);
    ofPushMatrix();
//    ofSetColor(255,255,255,100);
//    mHex.bind();
//    mRect.draw();
//    mHex.unbind();
    ofPopMatrix();
    
    ofTranslate(0,0,10);
    ofPushMatrix();
  //  ofSetColor(255,255,255,255);
   // mGround.bind();
   // mRect.draw();
    //mGround.unbind();
    ofPopMatrix();
    
    ofTranslate(0,0,10);
    ofPushMatrix();
 //   ofSetColor(255,255,255,255);
    mTree.bind();
    mRect.draw();
    mTree.unbind();
    ofPopMatrix();
    
    
    
	mFlowerParticles.draw();
    ofPopMatrix();
}


void testApp::keyPressed  (int key)
{
    switch(key)
    {
		case 'f':
			ofToggleFullscreen();
			break;
        default:
            break;
    }
}


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

void testApp::mouseDragged(int x, int y, int button)
{

}

