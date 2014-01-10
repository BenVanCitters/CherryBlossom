//
//  FlowerParticleSystem.cpp
//  CherryBlossoms
//
//  Created by Ben Van Citters on 1/8/14.
//
//

#include "FlowerParticleSystem.h"

static const float MOMENTUM = 0.5f;
static const float FLUID_FORCE = 0.6f;
FlowerParticleSystem::FlowerParticleSystem()
{
    for(int i = 0; i < FLOWER_COUNT; i++)
    {
        mBlossoms[i] = BlossomParticle(FLOWER_IMG_COUNT);
    }
    
    for(int i = 0; i < FLOWER_IMG_COUNT; i++)
    {
        std::stringstream sStream;
        sStream << "blossomImages/sakura" << (i+1) << ".png";
        mPetalImgs[i].loadImage(sStream.str());
    }
}

void FlowerParticleSystem::update(const msa::fluid::Solver &solver)
{
    ofVec2f windowSize = ofGetWindowSize();
    ofVec2f windowTrans = 1.f / windowSize;
    ofVec2f gravity(0,2);
//    windowTrans  = 
    //move the particles
//    for( std::vector<BlossomParticle>::iterator it = mBlossoms.begin(); it < mBlossoms.end(); it++)
    for(int i = 0; i < FLOWER_COUNT; i++)
    {
        mBlossoms[i].mVel =solver.getVelocityAtPos( mBlossoms[i].mPos * windowTrans ) * (mBlossoms[i].mMass * FLUID_FORCE ) * windowSize + mBlossoms[i].mVel * MOMENTUM;
        mBlossoms[i].mVel += gravity;
        mBlossoms[i].mPos +=  mBlossoms[i].mVel;
        
        if(mBlossoms[i].mPos.y > windowSize.y ||
           mBlossoms[i].mPos.x > windowSize.x ||
           mBlossoms[i].mPos.y < 0 ||
           mBlossoms[i].mPos.x < 0)
        {
            mBlossoms[i] = BlossomParticle(FLOWER_IMG_COUNT);
        }
        //vel = solver.getVelocityAtPos( pos * invWindowSize ) * (mass * FLUID_FORCE ) * windowSize + vel * MOMENTUM;
    }
}

void FlowerParticleSystem::draw()
{
    ofEnableAlphaBlending();
    ofEnableNormalizedTexCoords();
    
	ofSetColor(255);
    
//    ofColor(255,255,255);
    for(int i = 0; i < FLOWER_COUNT; i++)
    {
        mPetalImgs[mBlossoms[i].mImgIndex].getTextureReference().bind();
        mBlossoms[i].draw();
        mPetalImgs[mBlossoms[i].mImgIndex].getTextureReference().unbind();
    }
}

void FlowerParticleSystem::addParticle()
{
    
}

void FlowerParticleSystem::addParticle(const ofVec3f &pos)
{
    
}