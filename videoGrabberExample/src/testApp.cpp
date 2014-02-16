#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
    hexImag.loadImage("hex768.png");
    
	camWidth 		= 320;	// try to grab at this size. 
	camHeight 		= 240;
	
    //we can now get back a list of devices. 
	vector<ofVideoDevice> devices = vidGrabber.listDevices();
	
    for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName; 
        if( devices[i].bAvailable ){
            cout << endl;
        }else{
            cout << " - unavailable " << endl; 
        }
	}
    
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);
	
	videoInverted 	= new unsigned char[camWidth*camHeight*4];
	videoTexture.allocate(camWidth,camHeight, GL_RGBA);
	ofSetVerticalSync(true);
}


//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(100,100,100);
	
	vidGrabber.update();
	
	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight;
		unsigned char * pixels = vidGrabber.getPixels();
        unsigned char* maskPix = hexImag.getPixels();
        float vidIndexToMask = (hexImag.width*hexImag.height)*1.f/(vidGrabber.width*vidGrabber.height);
		for (int i = 0; i < totalPixels; i++){
            int index = i/4;
            
            int mIndex = (int)(vidIndexToMask*i);
            
			videoInverted[i+0] = pixels[i*3];
            videoInverted[i+1] = pixels[i*3+1];
            videoInverted[i+2] = pixels[i*3+2];
            videoInverted[i+3] = maskPix[i*3+3];
		}
		videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGBA);
	}

}



//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0xffffff);
	vidGrabber.draw(20,20);
	videoTexture.draw(20+camWidth,20,camWidth,camHeight);
//    hexImag.draw(0,0);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
	// in fullscreen mode, on a pc at least, the 
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...
	
	// Video settings no longer works in 10.7
	// You'll need to compile with the 10.6 SDK for this
    // For Xcode 4.4 and greater, see this forum post on instructions on installing the SDK
    // http://forum.openframeworks.cc/index.php?topic=10343        
	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
	
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
