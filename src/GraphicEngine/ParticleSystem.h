#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <irrlicht/irrlicht.h>
#include <Types.h>
#include <MathEngine/Vector3.h>
#include <MathEngine/Color.h>
#include "Window.h"
#include "SceneNode.h"

using namespace irr;

class ParticleSystem {
    
    public:
        ParticleSystem(SceneNode* parent, i32 id, Vector3<f32> position = Vector3<f32>(), Vector3<f32> rotation = Vector3<f32>(), Vector3<f32> scale = Vector3<f32>(1, 1, 1));
        ~ParticleSystem();
        void clearParticles();
        void createAttractionAffector(Vector3<f32> point, f32 speed = 1.0f,	bool attract = true, bool affectX = true, bool affectY = true, bool affectZ = true); 	
        void createFadeOutParticleAffector(i32 colorR = 0, i32 colorG = 0, i32 colorB = 0, i32 colorA = 0, i32 timeNeededToFadeOut = 1000);
        void createGravityAffector(Vector3<f32> gravity = Vector3<f32>(0, -0.03, 0), i32 timeForceLost = 1000); 	
        void createPointEmitter(Vector3<f32> direction = Vector3<f32>(0, 0.03, 0), i32	minParticlesPerSecond = 5, i32 maxParticlesPerSecond = 10, Color minStartColor = Color(255, 0, 0, 0), Color maxStartColor = Color(255, 255, 255, 255), i32	lifeTimeMin = 2000, i32 lifeTimeMax = 4000, i32 maxAngleDegrees = 0, Vector2<f32> minStartSize = Vector2<f32>(5, 5), Vector2<f32> maxStartSize = Vector2<f32>(5, 5));
        void createRotationAffector(Vector3<f32> speed = Vector3<f32>(5, 5, 5), Vector3<f32> pivotPoint = Vector3<f32>(0, 0, 0));
        void createScaleParticleAffector(Vector2<f32> scaleTo = Vector2<f32>(1, 1));
        void createSphereEmitter(Vector3<f32> center, f32 radius, Vector3<f32> direction = Vector3<f32>(0, 0.03, 0), i32 minParticlesPerSecond = 5, i32 maxParticlesPerSecond = 10, Color minStartColor = Color(255, 0, 0, 0), Color maxStartColor = Color(255, 255, 255, 255), i32 lifeTimeMin = 2000, i32 lifeTimeMax = 4000, i32 maxAngleDegrees = 0, Vector2<f32> minStartSize = Vector2<f32>(5, 5), Vector2<f32> maxStartSize = Vector2<f32>(5, 5)); 		 	
        void doParticleSystem(i32 time);
        void removeAllAffectors();
        void setParticlesAreGlobal(bool	global = true);
        void setParticleSize(Vector2<f32> size);

    private:
        scene::IParticleSystemSceneNode* particleSystemNode;
};

#endif