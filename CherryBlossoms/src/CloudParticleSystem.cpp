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

    
    float wxh[2]={400,200};
    mRect.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    mRect.addVertex(ofVec3f(0,0,0));
    mRect.addTexCoord(ofVec2f(0,0));
    
    mRect.addVertex(ofVec3f(0,wxh[1],0));
    mRect.addTexCoord(ofVec2f(0,1));
    
    mRect.addVertex(ofVec3f(wxh[0],0,0));
    mRect.addTexCoord(ofVec2f(1,0));
    
    mRect.addVertex(ofVec3f(wxh[0],wxh[1],0));
    mRect.addTexCoord(ofVec2f(1,1));

    for(int i = 0; i < CLOUD_COUNT; i++)
    {
        mClouds[i].mCloudImageIndex = (int)(ofRandom(CLOUD_IMAGE_COUNT));
        mClouds[i].mPos = ofVec3f(ofRandom(ofGetScreenWidth()),ofRandom(ofGetScreenHeight()/2.f),-150);
        mClouds[i].mVel = ofVec3f(ofRandom(20)-10,0,0);
    }
}

void CloudParticleSystem::update()
{
    for(int i = 0; i < CLOUD_COUNT; i++)
    {
        mClouds[i].mPos += mClouds[i].mVel;
        if(mClouds[i].mPos.x > ofGetWindowWidth())
        {
            mClouds[i].mPos.x = 0;
        }
        else if(mClouds[i].mPos.x < 0)
        {
            mClouds[i].mPos.x = ofGetWindowWidth();
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
    for(int i = 0; i < CLOUD_COUNT; i++)
    {
        ofPushMatrix();
        ofTranslate(mClouds[i].mPos);
        mCloudImgs[mClouds[i].mCloudImageIndex].bind();
        mRect.draw();
        mCloudImgs[mClouds[i].mCloudImageIndex].unbind();
        ofPopMatrix();
    }
}