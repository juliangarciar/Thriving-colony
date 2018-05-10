#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <irrlicht/irrlicht.h>
#include <Types.h>
#include <MathEngine/Vector3.h>
#include <MathEngine/Color.h>
#include "SceneNode.h"
#include "Window.h"

using namespace irr;

class ParticleSystem {
    
    public:
        ParticleSystem(SceneNode* parent, i32 id, Vector3<f32> position, Vector3<f32> rotation, Vector3<f32> scale);
        ~ParticleSystem();
        void addAffector(ParticleAffector* pa);
        void clearParticles();
        void createAttractionAffector(Vcetor3<f32> point, f32 speed = 1.0f,	bool attract = true, bool affectX = true, bool affectY = true, bool affectZ = true); 	

    private:
        scene::IParticleSystemSceneNode* particleSystemNode;
};

#endif