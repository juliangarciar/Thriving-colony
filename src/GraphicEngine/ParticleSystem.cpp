#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(SceneNode* parent, i32 id, Vector3<f32> position, Vector3<f32> rotation, Vector3<f32> scale) {
    scene::ISceneManager *smgr = Window::Instance() -> getSceneManager();
    particleSystemNode = smgr -> addParticleSystemSceneNode(false, parent -> getSceneNode(), id, core::vector3df(position.x, position.y, position.z), core::vector3df(rotation.x, rotation.y, rotation.z), core::vector3df(scale.x, scale.y, scale.z));
}

ParticleSystem::~ParticleSystem() {
    clearParticles();
}

void ParticleSystem::clearParticles() {
    particleSystemNode -> clearParticles();
}

void ParticleSystem::createAttractionAffector(Vector3<f32> point, f32 speed, bool attract, bool affectX, bool affectY, bool affectZ) {
    particleSystemNode -> addAffector(particleSystemNode -> createAttractionAffector(core::vector3df(point.x, point.y, point.z), speed, attract, affectX, affectY, affectZ));
}

void ParticleSystem::createFadeOutParticleAffector(i32 colorR, i32 colorG, i32 colorB, i32 colorA, i32 timeNeededForFadeOut) {
    particleSystemNode -> addAffector(particleSystemNode -> createFadeOutParticleAffector(video::SColor(colorR, colorG, colorB, colorA), timeNeededForFadeOut));
}

void ParticleSystem::createGravityAffector(Vector3<f32> gravity, i32 timeForceLost) {
    particleSystemNode -> addAffector(particleSystemNode -> createGravityAffector(core::vector3df(gravity.x, gravity.y, gravity.z), timeForceLost));
}

void ParticleSystem::createPointEmitter(Vector3<f32> direction, i32	minParticlesPerSecond, i32 maxParticlesPerSecond, Color minStartColor, Color maxStartColor, i32	lifeTimeMin, i32 lifeTimeMax, i32 maxAngleDegrees, Vector2<f32> minStartSize, Vector2<f32> maxStartSize) {
    particleSystemNode -> createPointEmitter(core::vector3df(direction.x, direction.y, direction.z), minParticlesPerSecond, maxParticlesPerSecond, video::SColor(minStartColor.r, minStartColor.g, minStartColor.b, minStartColor.a), video::SColor(maxStartColor.r, maxStartColor.g, maxStartColor.b, maxStartColor.a), lifeTimeMin, lifeTimeMax, maxAngleDegrees, core::dimension2df(minStartSize.x, minStartSize.y), core::dimension2df(maxStartSize.x, maxStartSize.y));
}

void ParticleSystem::createRotationAffector(Vector3<f32> speed, Vector3<f32> pivotPoint) {
    particleSystemNode -> addAffector(particleSystemNode -> createRotationAffector(core::vector3df(speed.x, speed.y, speed.z), core::vector3df(pivotPoint.x, pivotPoint.y, pivotPoint.z)));
}

void ParticleSystem::createScaleParticleAffector(Vector2<f32> scaleTo) {
    particleSystemNode -> addAffector(particleSystemNode -> createScaleParticleAffector(core::dimension2df(scaleTo.x, scaleTo.y)));
}

void ParticleSystem::createSphereEmitter(Vector3<f32> center, f32 radius, Vector3<f32> direction, i32 minParticlesPerSecond, i32 maxParticlesPerSecond, Color minStartColor, Color maxStartColor, i32 lifeTimeMin, i32 lifeTimeMax, i32 maxAngleDegrees, Vector2<f32> minStartSize, Vector2<f32> maxStartSize) {
    particleSystemNode -> createSphereEmitter(core::vector3df(center.x, center.y, center.z), radius, core::vector3df(direction.x, direction.y, direction.z), minParticlesPerSecond, maxParticlesPerSecond, video::SColor(minStartColor.r, minStartColor.g, minStartColor.b, minStartColor.a), video::SColor(maxStartColor.r, maxStartColor.g, maxStartColor.b, maxStartColor.a), lifeTimeMin, lifeTimeMax, maxAngleDegrees, core::dimension2df(minStartSize.x, minStartSize.y), core::dimension2df(maxStartSize.x, maxStartSize.y));
}

void ParticleSystem::doParticleSystem(i32 time) {
    particleSystemNode -> doParticleSystem(time);
}

void ParticleSystem::removeAllAffectors() {
    particleSystemNode -> removeAllAffectors();
}

void ParticleSystem::setParticlesAreGlobal(bool global) {
    particleSystemNode -> setParticlesAreGlobal(global);
}

void ParticleSystem::setParticleSize(Vector2<f32> size) {
    particleSystemNode -> setParticleSize(core::dimension2df(size.x, size.y));
}