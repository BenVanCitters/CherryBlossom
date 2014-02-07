#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofLog(OF_LOG_NOTICE, "loading the images...");
	mTree.loadImage("backgroundImages/tree.png");
    mFuji.loadImage("backgroundImages/mtn.png");
    mGround.loadImage("backgroundImages/ground.png");
    mHex.loadImage("backgroundImages/hex.png");
    
    mRect.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mRect.addVertex(ofVec3f(0,0,0));
    mRect.addTexCoord(ofVec2f(0,0));
    
    mRect.addVertex(ofVec3f(0,768,0));
    mRect.addTexCoord(ofVec2f(0,1));
    
    mRect.addVertex(ofVec3f(1024,0,0));
    mRect.addTexCoord(ofVec2f(1,0));
    
    mRect.addVertex(ofVec3f(1024,768,0));
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
    

    ofTranslate(300,
                0,
                -100);
    ofPushMatrix();
    ofTranslate(-500,-300);
    mFuji.bind();
    mRect.draw();
    mFuji.unbind();
    ofPopMatrix();
    
    ofTranslate(0,0,1);
    ofPushMatrix();
    ofTranslate(500,-300);
    mHex.bind();
    mRect.draw();
    mHex.unbind();
    ofPopMatrix();
    
    ofTranslate(0,0,1);
    ofPushMatrix();
    ofTranslate(-500,300);
    mGround.bind();
    mRect.draw();
    mGround.unbind();
    ofPopMatrix();
    
    ofTranslate(0,0,1);
    ofPushMatrix();
    ofTranslate(500,300);
    mTree.bind();
    mRect.draw();
    mTree.unbind();
    ofPopMatrix();
    
    ofPopMatrix();
    
	mFlowerParticles.draw();
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

