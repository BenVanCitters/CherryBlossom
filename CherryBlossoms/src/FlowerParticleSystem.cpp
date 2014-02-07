//
//  FlowerParticleSystem.cpp
//  CherryBlossoms
//
//  Created by Ben Van Citters on 1/8/14.
//
//

#include "FlowerParticleSystem.h"

static const float MOMENTUM = .05f;
static const float FLUID_FORCE = 0.6f;
FlowerParticleSystem::FlowerParticleSystem()
{
    initVBO();
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

void FlowerParticleSystem::update()
{
    ofVec2f windowSize = ofGetWindowSize();
    ofVec2f windowTrans = 1.f / windowSize;
    ofVec2f gravity(0,6);
    //move the particles
//    for( std::vector<BlossomParticle>::iterator it = mBlossoms.begin(); it < mBlossoms.end(); it++)
    for(int i = 0; i < FLOWER_COUNT; i++)
    {
        if( mBlossoms[i].mState == blossomStateFalling)
        {
            mBlossoms[i].mVel += gravity/mBlossoms[i].mMass;
            mBlossoms[i].mPos +=  mBlossoms[i].mVel;
            
            if(mBlossoms[i].mPos.y > windowSize.y ||
               mBlossoms[i].mPos.x > windowSize.x ||
               mBlossoms[i].mPos.y < 0 ||
               mBlossoms[i].mPos.x < 0)
            {
                mBlossoms[i] = BlossomParticle(FLOWER_IMG_COUNT);
            }
        }
        mBlossoms[i].update();
    }
}
void FlowerParticleSystem::initVBO()
{
    
    float sqrt2Div2 = sqrt(2.f)/2.f;
    const ofIndexType Faces[] = {0,1,2,
        0,2,3,
        0,3,4,
        0,4,1};
    
    ofVec3f v[5]= {ofVec3f(0,0,0),
        ofVec3f(-sqrt2Div2,sqrt2Div2, sqrt2Div2),
        ofVec3f(sqrt2Div2,sqrt2Div2, sqrt2Div2),
        ofVec3f(sqrt2Div2,-sqrt2Div2, sqrt2Div2),
        ofVec3f(-sqrt2Div2,-sqrt2Div2, sqrt2Div2)};
    
    //    ofVec3f n[5]= {ofVec3f(0,0,1),
    //                   ofVec3f(0,0,1),
    //                   ofVec3f(0,0,1),
    //                   ofVec3f(0,0,1),
    //                   ofVec3f(0,0,1)};
    //
    ofVec2f t[5]= {ofVec3f(.5f,.5f),
        ofVec3f(0,0),
        ofVec3f(1,0),
        ofVec3f(1,1),
        ofVec3f(0,1)};
    
    mQuad.setVertexData( v, 5, GL_STATIC_DRAW );
    mQuad.setTexCoordData( &t[0], 5, GL_STATIC_DRAW );
    mQuad.setIndexData( Faces, 12, GL_STATIC_DRAW );
    
}
void FlowerParticleSystem::draw()
{
    float tm = ofGetElapsedTimef();
    ofEnableAlphaBlending();
    ofEnableNormalizedTexCoords();
    
    ofPushMatrix();
	ofSetColor(255);
    for(int i = 0; i < FLOWER_COUNT; i++)
    {
        mPetalImgs[mBlossoms[i].mImgIndex].getTextureReference().bind();
        drawBlossom(&mBlossoms[i],tm);
        mPetalImgs[mBlossoms[i].mImgIndex].getTextureReference().unbind();
    }
    ofPopMatrix();
}

void FlowerParticleSystem::drawBlossom(BlossomParticle* b, float tm)
{
    ofSetColor(255,255,255);
    ofPushMatrix();
    ofTranslate(b->mPos);
    if(b->mState == blossomStateFalling)
    {
        ofRotateX(b->mRots.x*tm);
        ofRotateY(b->mRots.y*tm);
        ofRotateZ(b->mRots.z*tm);
    }
    else if(b->mState == blossomStateGrowing)
    {
        float pct = b->getGrowPct(tm);
        
        ofScale(pct,pct, MIN(pct*4,1));
    }
    float scl = 20.f;
    ofScale(scl,scl,scl);
    mQuad.drawElements( GL_TRIANGLES, 12);
    ofPopMatrix();
}

void FlowerParticleSystem::addParticle()
{
    
}

void FlowerParticleSystem::addParticle(const ofVec3f &pos)
{
    
}