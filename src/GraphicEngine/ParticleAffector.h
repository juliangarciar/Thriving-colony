#ifndef PARTICLEAFFECTOR_H
#define PARTICLEAFFECTOR_H

#include <irrlicht/irrlicht.h>
#include <Types.h>
#include <MathEngine/Vector3.h>
#include <MathEngine/Color.h>
#include "SceneNode.h"
#include "Window.h"

using namespace irr;

class ParticleAffector {
    
    public:
        ParticleAffector();
        ~ParticleAffector();

        scene::IParticleAffectorSceneNode* getParticleAffectorNode();

    private:
        scene::IParticleAffectorSceneNode* particleAffectorNode;
};

#endif