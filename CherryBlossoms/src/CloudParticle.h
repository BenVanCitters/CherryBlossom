//
//  CloudParticle.h
//  CherryBlossoms
//
//  Created by Ben Van Citters on 2/8/14.
//
//

#ifndef __CherryBlossoms__CloudParticle__
#define __CherryBlossoms__CloudParticle__

#include <iostream>
#include "ofMain.h"

class CloudParticle
{
public:
    
    ofVec3f mPos;
    ofVec3f mVel;
    int mCloudImageIndex;
};

#endif /* defined(__CherryBlossoms__CloudParticle__) */
