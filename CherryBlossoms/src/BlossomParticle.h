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
    void draw();
    void update();

private:
    ofVbo mQuad;
    ofVec2f mVel;
    ofVec2f mPos;
    float mMass;
};

#endif /* defined(__CherryBlossoms__BlossomParticle__) */
