//
//  FlowerParticleSystem.cpp
//  CherryBlossoms
//
//  Created by Ben Van Citters on 1/8/14.
//
//

#include "FlowerParticleSystem.h"

static const float MOMENTUM = .15f;
static const float FLUID_FORCE = 4.6f;
FlowerParticleSystem::FlowerParticleSystem()
{
    initVBO();
    mUseTextures = true;
    mShowFlowerStats = false;
    //load all flower images
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
                ofVec3f pos(i,j,ofRandom(4.f)-2.f);
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

void FlowerParticleSystem::update(const msa::fluid::Solver &solver)
{
    float tm = ofGetElapsedTimef();
    ofVec2f windowSize = ofGetWindowSize();
    ofVec2f windowTrans = 1.f / windowSize;
    ofVec2f gravity(0.f,3.f);
    //move the particles
//    for( std::vector<BlossomParticle>::iterator it = mBlossoms.begin(); it < mBlossoms.end(); it++)
    for(int i = 0; i < FLOWER_COUNT; i++)
    {
        if( mBlossoms[i].mState == blossomStateFalling)
        {
            //accel particle
            mBlossoms[i].mVel =solver.getVelocityAtPos( mBlossoms[i].mPos * windowTrans ) * (mBlossoms[i].mMass * FLUID_FORCE ) * windowSize/mBlossoms[i].mMass;
            mBlossoms[i].mVel += mBlossoms[i].mVel * MOMENTUM;
            
            mBlossoms[i].mVel += gravity/mBlossoms[i].mMass;
            mBlossoms[i].mVel += ofSignedNoise(mBlossoms[i].mPos.x,mBlossoms[i].mPos.y,mBlossoms[i].mPos.z,tm/1500.f)/mBlossoms[i].mMass;
            
            mBlossoms[i].mPos +=  mBlossoms[i].mVel;
            
            if(mBlossoms[i].mPos.y > windowSize.y+50 ||
               mBlossoms[i].mPos.x > windowSize.x+50 ||
               mBlossoms[i].mPos.y < 0 ||
               mBlossoms[i].mPos.x < 0 - 50)
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
    float szMult = 2.5f;
    float sqrt2Div2 = sqrt(2.f)/2.f;
    const ofIndexType Faces[] = {0,1,2,
        0,2,3,
        0,3,4,
        0,4,1};
    sqrt2Div2 *= szMult;
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
void FlowerParticleSystem::draw(float near_z, float far_z)
{
    long long tm = ofGetElapsedTimeMillis();
    ofEnableAlphaBlending();
    ofEnableNormalizedTexCoords();
    
    ofPushMatrix();
	ofSetColor(255);
    int waitinCount = 0, growingCount = 0, fallingcount = 0;
    for(int i = 0; i < FLOWER_COUNT; i++)
    {
        switch (mBlossoms[i].mState) {
            case blossomStateFalling:
                fallingcount++;
                break;
            case blossomStateGrowing:
                growingCount++;
                break;
            case blossomStateWaiting:
                waitinCount++;
                break;
            default:
                break;
        }
    }
    stringstream s;
    s <<"growing:" << growingCount << " waiting: " << waitinCount << " falling: " << fallingcount;
    string flowerStats = s.str();
    
    if(mUseTextures)
        for(int i = 0; i < FLOWER_COUNT; i++)
        {
            if ((near_z < mBlossoms[i].mPos.z) && (mBlossoms[i].mPos.z <= far_z))
            {
                mPetalImgs[mBlossoms[i].mImgIndex].getTextureReference().bind();
                drawBlossom(&mBlossoms[i],tm);
                mPetalImgs[mBlossoms[i].mImgIndex].getTextureReference().unbind();
            }
        }
    else
        for(int i = 0; i < FLOWER_COUNT; i++)
        {
            drawBlossom(&mBlossoms[i],tm);
        }
    ofPopMatrix();
    if(mShowFlowerStats)
        ofDrawBitmapString(flowerStats, 50,50);
}

void FlowerParticleSystem::drawBlossom(BlossomParticle* b, long long tm)
{
    ofSetColor(255,255,255);
    ofPushMatrix();
    ofVec3f nPos = b->mPos/ofVec3f(1920,1080,1) *ofGetWindowSize();
    ofTranslate(nPos);
    if(b->mState == blossomStateFalling)
    {
        ofRotateX(b->mRots.x*tm/1000.f);
        ofRotateY(b->mRots.y*tm/1000.f);
        ofRotateZ(b->mRots.z*tm/1000.f);
    }
    else if(b->mState == blossomStateGrowing || b->mState == blossomStateWaiting)
    {
        ofRotateX(b->mRots.x*b->mWaitStopTime/1000.f);
        ofRotateY(b->mRots.y*b->mWaitStopTime/1000.f);
        ofRotateZ(b->mRots.z*b->mWaitStopTime/1000.f);
        if(b->mState == blossomStateGrowing)
        {
            float pct = b->getGrowPct(tm);
            ofScale(pct,pct, MIN(pct*4,1));
        }
    }
    float scl = 17.f;
    ofScale(scl,scl,scl);
    if(mUseTextures)
        mQuad.drawElements( GL_TRIANGLE_STRIP, 12);
    else
        mQuad.drawElements( GL_LINE_STRIP, 12);
    ofPopMatrix();
}

void FlowerParticleSystem::addParticle()
{
    
}

void FlowerParticleSystem::addParticle(const ofVec3f &pos)
{
    
}
