//
//  FlowerParticleSystem.h
//  CherryBlossoms
//
//  Created by Ben Van Citters on 1/8/14.
//
//

#ifndef __CherryBlossoms__FlowerParticleSystem__
#define __CherryBlossoms__FlowerParticleSystem__

#include <iostream>
#include "BlossomParticle.h"

#define FLOWER_COUNT 500
#define FLOWER_IMG_COUNT 5

class FlowerParticleSystem
{
public:
    FlowerParticleSystem();
    void update();
    void draw();
    void addParticle();
	void addParticle(const ofVec3f &pos);
    
    ofImage mPetalImgs[5];
private:
    void drawBlossom(BlossomParticle* b, float tm);
    void initVBO();
    BlossomParticle mBlossoms[FLOWER_COUNT];
    ofVbo mQuad;
};

#endif /* defined(__CherryBlossoms__FlowerParticleSystem__) */
