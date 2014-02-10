//
//  CloudParticleSystem.cpp
//  CherryBlossoms
//
//  Created by Ben Van Citters on 2/8/14.
//
//

#include "CloudParticleSystem.h"


CloudParticleSystem::CloudParticleSystem()
{
    //load cloud images
    for(int i = 0; i < CLOUD_IMAGE_COUNT; i++)
    {
        std::stringstream sStream;
        sStream << "cloudImages/cloud" << (i+1) << ".png";
        mCloudImgs[i].loadImage(sStream.str());
    }

    
    float wxh[2]={1200,400};
    mRect.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mRect.addVertex(ofVec3f(0,0,0));
    mRect.addTexCoord(ofVec2f(0,0));
    
    mRect.addVertex(ofVec3f(0,wxh[1],0));
    mRect.addTexCoord(ofVec2f(0,1));
    
    mRect.addVertex(ofVec3f(wxh[0],0,0));
    mRect.addTexCoord(ofVec2f(1,0));
    
    mRect.addVertex(ofVec3f(wxh[0],wxh[1],0));
    mRect.addTexCoord(ofVec2f(1,1));
    
    mMinXExtent = -ofGetWindowWidth()*.5;
    mMaxXExtent = ofGetWindowWidth()*1.5;
    
    for(int i = 0; i < CLOUD_COUNT; i++)
    {
        mClouds[i].mCloudImageIndex = (int)(ofRandom(CLOUD_IMAGE_COUNT));
        mClouds[i].mPos = ofVec3f(mMinXExtent + ofRandom(mMaxXExtent-mMinXExtent),ofRandom(ofGetScreenHeight()*2.5),ofRandom(550));
        mClouds[i].mVel = ofVec3f(ofRandom(2)-1,0,0);
    }
}

void CloudParticleSystem::update()
{
    
    for(int i = 0; i < CLOUD_COUNT; i++)
    {
        mClouds[i].mPos += mClouds[i].mVel;
        if(mClouds[i].mPos.x > mMaxXExtent)
        {
            mClouds[i].mPos.x = mMinXExtent;
        }
        else if(mClouds[i].mPos.x < mMinXExtent)
        {
            mClouds[i].mPos.x = mMaxXExtent;
        }
        if(mClouds[i].mPos.y > ofGetWindowHeight())
        {
            mClouds[i].mPos.y = 0;
        }
        else if(mClouds[i].mPos.y < 0)
        {
            mClouds[i].mPos.y = ofGetWindowHeight();
        }
        
    }
}
void CloudParticleSystem::draw()
{
    ofSetColor(255,255,255,40);
    ofPushMatrix();
    ofRotateX(-70);
    for(int i = 0; i < CLOUD_COUNT; i++)
    {
        ofPushMatrix();
        ofTranslate(mClouds[i].mPos);
        mCloudImgs[mClouds[i].mCloudImageIndex].bind();
        mRect.draw();
        mCloudImgs[mClouds[i].mCloudImageIndex].unbind();
        ofPopMatrix();
    }
    ofPopMatrix();
}
