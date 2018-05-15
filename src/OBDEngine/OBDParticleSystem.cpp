#include "OBDParticleSystem.h"
#include "Graphics/TParticleSystem.h"

OBDParticleSystem::OBDParticleSystem(OBDSceneNode* parent, glm::vec3 pos) : OBDEntity(parent) {
    particleSystemNode = new TNode(new TParticleSystem()); 
	parent -> addChild(this);
    position = pos;
}

OBDParticleSystem::~OBDParticleSystem() {
    for (i32 i = 0; i < affectors.size(); i++) {
        delete affectors[i];
    }
    affectors.clear();
    delete emiter;
}

void OBDParticleSystem::setEmiter(OBDParticleEmiter* newEmiter) {
    delete emiter;
    emiter = newEmiter;
}

void OBDParticleSystem::addAffector(OBDParticleAffector* newAffector) {
    affectors.push_back(newAffector);
}

void OBDParticleSystem::clearAffectors() {
    for (i32 i = 0; i < affectors.size(); i++) {
        delete affectors[i];
    }
    affectors.clear();
}

void OBDParticleSystem::createPointEmitter(glm::vec3 direction, i32 particlesPerSecond, OBDColor startColor, i32 lifeTime, i32 maxAngleDegrees, glm::vec2 startSize) {
    std::vector<TParticle*> particles;
    for (i32 i = 0; i < particlesPerSecond; i ++) {
        particles.push_back(new TParticle(startColor, startColor, lifeTime, 0, position, direction, direction, startSize, startSize));
    }
}