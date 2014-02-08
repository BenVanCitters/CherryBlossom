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

    
    for(int i = 0; i < FLOWER_IMG_COUNT; i++)
    {
        std::stringstream sStream;
        sStream << "blossomImages/sakura" << (i+1) << ".png";
        mPetalImgs[i].loadImage(sStream.str());
    }
    
    ofImage treeMask;
    treeMask.loadImage("backgroundImages/1080/tree_nodes.png");
    //for each pixel add the position to the maks
    unsigned char* pixels = treeMask.getPixels();
    int curIndex = 0;
    for(int j = 0; j < treeMask.height; j++)
    {
        for(int i = 0; i < treeMask.width; i++)
        {
            if(pixels[curIndex*4+3] > 0)
            {
                ofVec3f pos(i,j,0);
                mTreePositions.push_back(pos);
            }
            curIndex++;
        }
    }
    
    for(int i = 0; i < FLOWER_COUNT; i++)
    {
        ofVec3f newPos;
        getNewBlossomPosition(&newPos);
        mBlossoms[i] = BlossomParticle(FLOWER_IMG_COUNT,newPos);
    }
}

void FlowerParticleSystem::getNewBlossomPosition(ofVec3f* pos)
{
    int randIndex = (int)(mTreePositions.size() * ofRandom(1.f));
    ofVec3f vPos = mTreePositions[randIndex];
    pos->x = vPos.x;
    pos->y = vPos.y;
    pos->z = vPos.z;
}

void FlowerParticleSystem::update()
{
    float tm = ofGetElapsedTimef();
    ofVec2f windowSize = ofGetWindowSize();
    ofVec2f windowTrans = 1.f / windowSize;
    ofVec2f gravity(0,6);
    //move the particles
//    for( std::vector<BlossomParticle>::iterator it = mBlossoms.begin(); it < mBlossoms.end(); it++)
    for(int i = 0; i < FLOWER_COUNT; i++)
    {
        if( mBlossoms[i].mState == blossomStateFalling)
        {
            mBlossoms[i].mVel += 1*ofSignedNoise(mBlossoms[i].mPos.x,mBlossoms[i].mPos.y,mBlossoms[i].mPos.z,tm/150.f)/mBlossoms[i].mMass;
            mBlossoms[i].mVel += (1.f/95.f)*gravity/mBlossoms[i].mMass;
            mBlossoms[i].mPos +=  mBlossoms[i].mVel;
            
            if(mBlossoms[i].mPos.y > windowSize.y ||
               mBlossoms[i].mPos.x > windowSize.x ||
               mBlossoms[i].mPos.y < 0 ||
               mBlossoms[i].mPos.x < 0)
            {
                ofVec3f newPos;
                getNewBlossomPosition(&newPos);
                mBlossoms[i] = BlossomParticle(FLOWER_IMG_COUNT,newPos);
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
    ofVec3f nPos = b->mPos/ofVec3f(1920,1080,1) *ofGetWindowSize();
    ofTranslate(nPos);
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