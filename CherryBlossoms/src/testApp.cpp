#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofLog(OF_LOG_NOTICE, "loading the images...");
//    mTreeMask.loadImage("backgroundImages/1080/tree_nodes.png");

    
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

//	windowResized(ofGetWidth(), ofGetHeight());		// force this at start (cos I don't think it is called)
	
//	ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);
}


void testApp::update()
{
    mFlowerParticles.update();
    mCloudParticles.update();
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
    mCloudParticles.draw();
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

