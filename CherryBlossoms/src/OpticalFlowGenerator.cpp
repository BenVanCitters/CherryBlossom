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
    mFlow.setPyramidScale(.4);
    mCam.initGrabber(320, 240);
    mStepSize = 8;
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

ofVec2f** OpticalFlowGenerator::getFlowVectors()
{
    return mFlowVectors;
}

ofVec2f OpticalFlowGenerator::getWHVector()
{
    return ofVec2f(mXSteps,mYSteps);
}

void OpticalFlowGenerator::update()
{
    mCam.update();
	if(mCam.isFrameNew())
    {
        mFlow.setWindowSize(8);
        mFlow.calcOpticalFlow(mCam);
         
         for(int y = 1; y + 1 < mYSteps; y++)
         {
             for(int x = 1; x + 1 < mXSteps; x++)
             {
                 int i = y * mXSteps + x;
                 ofVec2f position(x * mStepSize, y * mStepSize);
                 ofRectangle area(position - ofVec2f(mStepSize, mStepSize) / 2, mStepSize, mStepSize);
                 mFlowVectors[y][x] = mFlow.getAverageFlowInRegion(area)/4000.f;
//                 if(mFlowVectors[y][x].length() > 0)
//                     mFlowVectors[y][x].x = 1;
             }
         }

    }
}

void OpticalFlowGenerator::draw()
{
//    mCam.draw(0, 0);
    for(int y = 1; y + 1 < mYSteps; y++)
    {
        for(int x = 1; x + 1 < mXSteps; x++)
        {
            ofVec2f position(x * mStepSize, y * mStepSize);
            ofLine(position, position+mFlowVectors[y][x]*900);
        }
    }
}