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
#include "CloudParticle.h"

#define CLOUD_COUNT 5

using namespace std;
class CloudParticleSystem
{
public:
    CloudParticle mClouds[CLOUD_COUNT];

    CloudParticleSystem();
    void update();
    void draw();
};
#endif /* defined(__CherryBlossoms__CloudParticleSystem__) */
