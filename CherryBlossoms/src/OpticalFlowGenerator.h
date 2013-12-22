//
//  OpticalFlowGenerator.h
//  CherryBlossoms
//
//  Created by Ben Van Citters on 12/22/13.
//
//

#ifndef __CherryBlossoms__OpticalFlowGenerator__
#define __CherryBlossoms__OpticalFlowGenerator__

#include <iostream>
#include "ofMain.h"
#include "ofxCv.h"

class OpticalFlowGenerator
{
    ofVec2f** mFlowVectors;
    int mStepSize;
    ofVideoGrabber mCam;
	ofxCv::FlowFarneback mFlow;
    int mXSteps, mYSteps;
    
public:
    OpticalFlowGenerator();
    void draw();
    void update();
    ~OpticalFlowGenerator();
};

#endif /* defined(__CherryBlossoms__OpticalFlowGenerator__) */
