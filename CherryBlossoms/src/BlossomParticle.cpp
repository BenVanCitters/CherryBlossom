//
//  BlossomParticle.cpp
//  CherryBlossoms
//
//  Created by Ben Van Citters on 12/22/13.
//
//

#include "BlossomParticle.h"

BlossomParticle::BlossomParticle()
{
    
}

BlossomParticle::BlossomParticle(int imgCount, ofVec3f pos)
{
    mState = blossomStateGrowing;
    float maxRSpd = 70;
    mRots = ofVec3f(ofRandom(maxRSpd*2)-maxRSpd,
                    ofRandom(maxRSpd*2)-maxRSpd,
                    ofRandom(maxRSpd*2)-maxRSpd);
    mImgIndex = (int)(ofRandom(imgCount));
    mPos = pos; //ofVec3f(ofRandom(ofGetWindowWidth()),ofRandom(600),1200-ofRandom(4000) );
    mMass = 1+ofRandom(.5f);
    
    float tm = ofGetElapsedTimef();
    mGrowDur =ofRandom(30);
    mGrowStopTime = tm+ mGrowDur;
    mWaitStopTime = mGrowStopTime + ofRandom(15);
//    mWaitStopTime
//    float sqrt2Div2 = sqrt(2.f)/2.f;
//    const ofIndexType Faces[] = {0,1,2,
//        0,2,3,
//        0,3,4,
//        0,4,1};
//    //     ofVec3f n[12];
//    ofVec3f v[5]= {ofVec3f(0,0,-sqrt2Div2),
//        ofVec3f(-sqrt2Div2,sqrt2Div2, 0),
//        ofVec3f(sqrt2Div2,sqrt2Div2, 0),
//        ofVec3f(sqrt2Div2,-sqrt2Div2, 0),
//        ofVec3f(-sqrt2Div2,-sqrt2Div2, 0)};
//    
//    //    ofVec3f n[5]= {ofVec3f(0,0,1),
//    //                   ofVec3f(0,0,1),
//    //                   ofVec3f(0,0,1),
//    //                   ofVec3f(0,0,1),
//    //                   ofVec3f(0,0,1)};
//    //
//    ofVec2f t[5]= {ofVec3f(.5f,.5f),
//        ofVec3f(0,0),
//        ofVec3f(1,0),
//        ofVec3f(1,1),
//        ofVec3f(0,1)};
//    
//    mQuad.setVertexData( v, 5, GL_STATIC_DRAW );
//    mQuad.setTexCoordData( &t[0], 5, GL_STATIC_DRAW );
//    mQuad.setIndexData( Faces, 12, GL_STATIC_DRAW );
}

float BlossomParticle::getGrowPct(float curTime)
{
    return 1.f-(mGrowStopTime-curTime)/mGrowDur;
}

void BlossomParticle::update()
{
    float tm = ofGetElapsedTimef();
    switch(mState){
            case blossomStateGrowing:
                if(tm > mGrowStopTime)
                {
                    mState = blossomStateWaiting;
                }
                break;
            case blossomStateWaiting:
                if(tm > mWaitStopTime)
                {
                    mState = blossomStateFalling;
                }
                break;
//            case blossomStateFalling:
        default:
            break;
    }
}

void BlossomParticle::draw()
{
//    ofSetColor(255,255,255);
//    ofPushMatrix();
//    ofTranslate(mPos);
//    float tm = ofGetElapsedTimef();
//    ofRotateX(mRots.x*tm);
//    ofRotateY(mRots.y*tm);
//    ofRotateZ(mRots.z*tm);
//    
//    float scl = 20.f;
//    ofScale(scl,scl,scl);
//    mQuad.drawElements( GL_TRIANGLES, 12);
//    ofPopMatrix();
}