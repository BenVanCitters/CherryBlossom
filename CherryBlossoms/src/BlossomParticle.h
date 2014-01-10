//
//  BlossomParticle.h
//  CherryBlossoms
//
//  Created by Ben Van Citters on 12/22/13.
//
//

#ifndef __CherryBlossoms__BlossomParticle__
#define __CherryBlossoms__BlossomParticle__

#include <iostream>
#include "ofMain.h"
class BlossomParticle
{
public:
    
    BlossomParticle();
    BlossomParticle(int imgCount);
    void draw();
    void update();

    ofVbo mQuad;
    ofVec3f mVel;
    ofVec3f mPos;
    ofVec3f mRots;
    float mMass;
    
    int mImgIndex;
    
    bool mIsDead;
};

#endif /* defined(__CherryBlossoms__BlossomParticle__) */
