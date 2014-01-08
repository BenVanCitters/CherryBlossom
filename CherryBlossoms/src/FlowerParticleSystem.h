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
#include "MSAFluidSolver.h"

class FlowerParticleSystem
{
public:
    FlowerParticleSystem();
    void update(const msa::fluid::Solver &solver);
    void draw();
    void addParticle();
	void addParticle(const ofVec3f &pos);
private:
    std::vector<BlossomParticle> mBlossoms;
};

#endif /* defined(__CherryBlossoms__FlowerParticleSystem__) */
