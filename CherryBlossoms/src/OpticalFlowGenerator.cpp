//
//  OpticalFlowGenerator.cpp
//  CherryBlossoms
//
//  Created by Ben Van Citters on 12/22/13.
//
//

#include "OpticalFlowGenerator.h"

using namespace ofxCv;
using namespace cv;

OpticalFlowGenerator::OpticalFlowGenerator()
{
    mCam.initGrabber(320, 240);
    mStepSize = 6;
    mYSteps = mCam.getHeight() / mStepSize;
	mXSteps = mCam.getWidth() / mStepSize;
    mFlowVectors = new ofVec2f*[mYSteps];
    for(int y = 0; y < mYSteps; y++)
    {
        mFlowVectors[y] = new ofVec2f[mXSteps];
    }
}

OpticalFlowGenerator::~OpticalFlowGenerator()
{
    //delete vector array
    for(int y = 0; y < mYSteps; y++)
    {
        delete mFlowVectors[y];
    }
    delete mFlowVectors;
}

void OpticalFlowGenerator::update()
{
    mCam.update();
	if(mCam.isFrameNew())
    {
        mFlow.setWindowSize(8);
        mFlow.calcOpticalFlow(mCam);
        
        /*
         
         for(int i = 0; i < quads.size();i++)
         {
         ofRectangle area(quads[i].mPosition - ofVec2f(stepSize, stepSize) / 2, stepSize, stepSize);
         if(area.x > 0 && area.y > 0 && area.getRight() < 320 && area.getBottom() < 240)
         {
         ofVec2f vel =flow.getAverageFlowInRegion(area);
         quads[i].mVelocity = (quads[i].mVelocity+vel) *.4;
         
         }
         quads[i].update();
         }

         
         */
    }
}

void OpticalFlowGenerator::draw()
{
    for(int y = 1; y + 1 < mYSteps; y++)
    {
        for(int x = 1; x + 1 < mXSteps; x++)
        {
            ofVec2f position(x * mStepSize, y * mStepSize);
            ofLine(position, position+mFlowVectors[y][x]);
        }
    }
}