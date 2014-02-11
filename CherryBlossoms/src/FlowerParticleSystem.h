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

#define FLOWER_COUNT 100
#define FLOWER_IMG_COUNT 5

using namespace std;

class FlowerParticleSystem
{
public:
    FlowerParticleSystem();
    void update();
    void draw();
    void addParticle();
	void addParticle(const ofVec3f &pos);
    bool mShowFlowerStats;
    bool mUseTextures;
    
private:
    void drawBlossom(BlossomParticle* b, long long tm);
    void initVBO();
    void getNewBlossomPosition(ofVec3f* pos);
    
    ofImage mPetalImgs[5];
    BlossomParticle mBlossoms[FLOWER_COUNT];
    ofVbo mQuad;
    vector<ofVec3f> mTreePositions;

};

#endif /* defined(__CherryBlossoms__FlowerParticleSystem__) */
