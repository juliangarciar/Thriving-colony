#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(SceneNode* parent, i32 id, Vector3<f32> position, Vector3<f32> rotation, Vector3<f32> scale) {
    
}

ParticleSystem::~ParticleSystem() {
	
}

void ParticleSystem::clearParticles() {
	
}

void ParticleSystem::createAttractionAffector(Vector3<f32> point, f32 speed, bool attract, bool affectX, bool affectY, bool affectZ) {
	
}

void ParticleSystem::createFadeOutParticleAffector(i32 colorR, i32 colorG, i32 colorB, i32 colorA, i32 timeNeededForFadeOut) {
	
}

void ParticleSystem::createGravityAffector(Vector3<f32> gravity, i32 timeForceLost) {
	
}

void ParticleSystem::createPointEmitter(Vector3<f32> direction, i32	minParticlesPerSecond, i32 maxParticlesPerSecond, Color minStartColor, Color maxStartColor, i32	lifeTimeMin, i32 lifeTimeMax, i32 maxAngleDegrees, Vector2<f32> minStartSize, Vector2<f32> maxStartSize) {
	
}

void ParticleSystem::createRotationAffector(Vector3<f32> speed, Vector3<f32> pivotPoint) {
	
}

void ParticleSystem::createScaleParticleAffector(Vector2<f32> scaleTo) {
	
}

void ParticleSystem::createSphereEmitter(Vector3<f32> center, f32 radius, Vector3<f32> direction, i32 minParticlesPerSecond, i32 maxParticlesPerSecond, Color minStartColor, Color maxStartColor, i32 lifeTimeMin, i32 lifeTimeMax, i32 maxAngleDegrees, Vector2<f32> minStartSize, Vector2<f32> maxStartSize) {
	
}

void ParticleSystem::doParticleSystem(i32 time) {
	
}

void ParticleSystem::removeAllAffectors() {
	
}

void ParticleSystem::setParticlesAreGlobal(bool global) {
	
}

void ParticleSystem::setParticleSize(Vector2<f32> size) {
	
}