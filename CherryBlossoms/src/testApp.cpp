#include "testApp.h"

char sz[] = "[Rd9?-2XaUP0QY[hO%9QTYQ`-W`QZhcccYQY[`b";


float tuioXScaler = 1;
float tuioYScaler = 1;

//--------------------------------------------------------------
void testApp::setup()
{
	for(int i=0; i<strlen(sz); i++) sz[i] += 20;
	
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);

	
	windowResized(ofGetWidth(), ofGetHeight());		// force this at start (cos I don't think it is called)
	//pMouse = msa::getWindowCenter();
	
	ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);
}


void testApp::update()
{
    mFlowerParticles.update();
}

void testApp::draw()
{

    ofBackground(0,0,0);
	mFlowerParticles.draw();
//	ofDrawBitmapString(sz, 50, 50);
}


void testApp::keyPressed  (int key)
{
    switch(key) {
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
//	ofVec2f eventPos = ofVec2f(x, y);
//	ofVec2f mouseNorm = ofVec2f(eventPos) / ofGetWindowSize();
//	ofVec2f mouseVel = ofVec2f(eventPos - pMouse) / ofGetWindowSize();
//	pMouse = eventPos;
}

void testApp::mouseDragged(int x, int y, int button)
{
//	ofVec2f eventPos = ofVec2f(x, y);
//	ofVec2f mouseNorm = ofVec2f(eventPos) / ofGetWindowSize();
//	ofVec2f mouseVel = ofVec2f(eventPos - pMouse) / ofGetWindowSize();
//	pMouse = eventPos;
}

