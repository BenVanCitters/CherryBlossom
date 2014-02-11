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
enum blossomState{blossomStateGrowing,blossomStateWaiting,blossomStateFalling};
class BlossomParticle
{
public:
    
    BlossomParticle();
    BlossomParticle(int imgCount, ofVec3f pos);
    void draw();
    void update();

    float getGrowPct(long long curTime);
    
    ofVbo mQuad;
    ofVec3f mVel;
    ofVec3f mPos;
    ofVec3f mRots;
    float mMass;
    
    long long mGrowStopTime;
    long long mGrowDur;
    long long mWaitStopTime;
    
    int mImgIndex;
    blossomState mState;
    bool mIsDead;
};

#endif /* defined(__CherryBlossoms__BlossomParticle__) */
