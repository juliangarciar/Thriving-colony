#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(SceneNode* parent, i32 id, Vector3<f32> position, Vector3<f32> rotation, Vector3<f32> scale) {
    scene::ISceneManager *smgr = Window::Instance() -> getSceneManager();
    particleSystemNode = smgr -> addParticleSystemSceneNode(parent -> getSceneNode(), id, core::vector3df(position.x, position.y, position.z), core::vector3df(rotation.x, rotation.y, rotation.z), core::vector3df(scale.x, scale.y, scale.z));
}

ParticleSystem::~ParticleSystem() {
    clearParticles();
}

void ParticleSystem::addAffector(ParticleAffector* pa) {
    particleSystemNode -> addAffector(pa -> getParticleAffectorNode());
}

void ParticleSystem::clearParticles() {
    particleSystemNode -> clearParticles();
}

void ParticleSystem::createAttractionAffector(Vcetor3<f32> point, f32 speed, bool attract, bool affectX, bool affectY, bool affectZ) {
    particleSystemNode -> addAffector(particleSystemNode -> createAttractionAffector(core::vector3df(point.x, point.y, point.z), speed, attract, attractX, attractY, attractZ));
}