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
    const ofIndexType Faces[] = {0,1,2,3};
//     ofVec3f n[12];
    ofVec3f v[4]= {ofVec3f(0,1),
        ofVec3f(0,1),
        ofVec3f(0,1),
        ofVec3f(0,1)};
    ofVec3f n[4]= {ofVec3f(0,1),
        ofVec3f(0,1),
        ofVec3f(0,1),
        ofVec3f(0,1)};
    ofVec2f t[4]= {ofVec3f(0,1),
        ofVec3f(0,1),
        ofVec3f(0,1),
        ofVec3f(0,1)};
    for(int i = 0; i < 4; i++)
    {
        
    }
    mQuad.setVertexData( &v[0], 4, GL_STATIC_DRAW );
    mQuad.setTexCoordData( &t[0], 4, GL_STATIC_DRAW );
    mQuad.setIndexData( &Faces[0], 4, GL_STATIC_DRAW );

}

void BlossomParticle::update()
{
    
}

void BlossomParticle::draw()
{
    mQuad.drawElements( GL_TRIANGLES, 60);
}