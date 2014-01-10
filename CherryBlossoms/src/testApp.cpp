#include "testApp.h"

char sz[] = "[Rd9?-2XaUP0QY[hO%9QTYQ`-W`QZhcccYQY[`b";


float tuioXScaler = 1;
float tuioYScaler = 1;

//--------------------------------------------------------------
void testApp::setup()
{
	for(int i=0; i<strlen(sz); i++) sz[i] += 20;
	
	// setup fluid stuff
	fluidSolver.setup(100, 100);
    fluidSolver.enableRGB(true).setFadeSpeed(0.002).setDeltaT(0.5).setVisc(0.00015).setColorDiffusion(0);
	fluidDrawer.setup(&fluidSolver);
	
	fluidCellsX			= 150;
	
	drawFluid			= true;
	
	ofSetFrameRate(60);
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);

	
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
    gui.addSlider("tuioXScaler", tuioXScaler, 0, 2);
    gui.addSlider("tuioYScaler", tuioYScaler, 0, 2);
    
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


void testApp::fadeToColor(float r, float g, float b, float speed)
{
    glColor4f(r, g, b, speed);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());
}


// add force and dye to fluid, and create particles
void testApp::addToFluid(ofVec2f pos, ofVec2f vel, bool addColor, bool addForce)
{
    float speed = vel.x * vel.x  + vel.y * vel.y * msa::getWindowAspectRatio() * msa::getWindowAspectRatio();    // balance the x and y components of speed with the screen aspect ratio
    if(speed > 0)
    {
		pos.x = ofClamp(pos.x, 0.0f, 1.0f);
		pos.y = ofClamp(pos.y, 0.0f, 1.0f);
		
        int index = fluidSolver.getIndexForPos(pos);
		
//		if(addColor)
//        {
////			Color drawColor(CM_HSV, (getElapsedFrames() % 360) / 360.0f, 1, 1);
//			ofColor drawColor;
//			drawColor.setHsb((ofGetFrameNum() % 255), 255, 255);
//			
//			fluidSolver.addColorAtIndex(index, drawColor * colorMult);
//			
////            particleSystem.addParticles(pos * ofVec2f(ofGetWindowSize()), 10);
//		}
		
		if(addForce)
			fluidSolver.addForceAtIndex(index, vel * velocityMult);
    }
}


void testApp::update()
{
    mOpticalFlowGenerator.update();
    addForceFromOpticalFlow();
    mFlowerParticles.update(fluidSolver);
	
    if(resizeFluid)
    {
		fluidSolver.setSize(fluidCellsX, fluidCellsX / msa::getWindowAspectRatio());
		fluidDrawer.setup(&fluidSolver);
		resizeFluid = false;
	}
	fluidSolver.update();
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
                
                int index = fluidSolver.getIndexForPos(pos);
                
//                if(addColor)
//                {
//                    ofColor drawColor;
//                    drawColor.setHsb((ofGetFrameNum() % 255), 255, 255);
//                    
////                    particleSystem.addParticles(pos * ofVec2f(ofGetWindowSize()), 10);
//                }
                
                fluidSolver.addForceAtIndex(index, vel * velocityMult);
            }
        }
    }
}

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


void testApp::keyPressed  (int key)
{
    switch(key) {
		case '1':
			fluidDrawer.setDrawMode(msa::fluid::kDrawColor);
			break;

		case '2':
			fluidDrawer.setDrawMode(msa::fluid::kDrawMotion);
			break;

		case '3':
			fluidDrawer.setDrawMode(msa::fluid::kDrawSpeed);
			break;
			
		case '4':
			fluidDrawer.setDrawMode(msa::fluid::kDrawVectors);
			break;
    
		case 'd':
			drawFluid ^= true;
			break;
			
		case 'f':
			ofToggleFullscreen();
			break;
			
		case 'r':
			fluidSolver.reset();
			break;
			
		case 'b': {
//			Timer timer;
//			const int ITERS = 3000;
//			timer.start();
//			for(int i = 0; i < ITERS; ++i) fluidSolver.update();
//			timer.stop();
//			cout << ITERS << " iterations took " << timer.getSeconds() << " seconds." << std::endl;
		}
			break;
			
    }
}


//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
//	ofVec2f eventPos = ofVec2f(x, y);
//	ofVec2f mouseNorm = ofVec2f(eventPos) / ofGetWindowSize();
//	ofVec2f mouseVel = ofVec2f(eventPos - pMouse) / ofGetWindowSize();
//	addToFluid(mouseNorm, mouseVel, true, true);
//	pMouse = eventPos;
}

void testApp::mouseDragged(int x, int y, int button)
{
//	ofVec2f eventPos = ofVec2f(x, y);
//	ofVec2f mouseNorm = ofVec2f(eventPos) / ofGetWindowSize();
//	ofVec2f mouseVel = ofVec2f(eventPos - pMouse) / ofGetWindowSize();
//	addToFluid(mouseNorm, mouseVel, false, true);
//	pMouse = eventPos;
}

