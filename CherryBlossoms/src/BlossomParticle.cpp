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
    float sqrt2Div2 = sqrt(2.f)/2.f;
    const ofIndexType Faces[] = {0,1,2,
                                 0,2,3,
                                 0,3,4,
                                 0,4,1};
//     ofVec3f n[12];
    ofVec3f v[5]= {ofVec3f(0,0,sqrt2Div2),
                   ofVec3f(-sqrt2Div2,sqrt2Div2, 0),
                   ofVec3f(sqrt2Div2,sqrt2Div2, 0),
                   ofVec3f(sqrt2Div2,-sqrt2Div2, 0),
                   ofVec3f(-sqrt2Div2,-sqrt2Div2, 0)};
    
    ofVec3f n[5]= {ofVec3f(0,0,1),
                   ofVec3f(0,0,1),
                   ofVec3f(0,0,1),
                   ofVec3f(0,0,1),
                   ofVec3f(0,0,1)};
    
    ofVec2f t[5]= {ofVec3f(.5,.5),
                   ofVec3f(0,0),
                   ofVec3f(1,0),
                   ofVec3f(1,1),
                   ofVec3f(0,1)};

    mQuad.setVertexData( &v[0], 4, GL_STATIC_DRAW );
    mQuad.setTexCoordData( &t[0], 4, GL_STATIC_DRAW );
    mQuad.setIndexData( &Faces[0], 4, GL_STATIC_DRAW );
}

void BlossomParticle::update()
{
    
}

void BlossomParticle::draw()
{
    ofPushMatrix();
    mQuad.drawElements( GL_TRIANGLES, 60);
    ofPopMatrix();
}