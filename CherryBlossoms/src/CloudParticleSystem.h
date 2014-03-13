//
//  CloudParticleSystem.h
//  CherryBlossoms
//
//  Created by Ben Van Citters on 2/8/14.
//
//

#ifndef __CherryBlossoms__CloudParticleSystem__
#define __CherryBlossoms__CloudParticleSystem__

#include <iostream>

#include "ofMain.h"
#include "CloudParticle.h"

#define CLOUD_COUNT 10
#define CLOUD_IMAGE_COUNT 3

using namespace std;
class CloudParticleSystem
{
    
    CloudParticle mClouds[CLOUD_COUNT];
    ofVboMesh mRect;
    ofImage mCloudImgs[3];
    float mMinXExtent;
    float mMaxXExtent;
public:


    CloudParticleSystem();
    void update();
    void draw();
};
#endif /* defined(__CherryBlossoms__CloudParticleSystem__) */
