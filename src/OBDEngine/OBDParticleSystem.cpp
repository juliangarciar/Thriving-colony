#include "OBDParticleSystem.h"
#include "Graphics/TParticleSystem.h"

OBDParticleSystem::OBDParticleSystem(OBDSceneNode* parent) : OBDEntity(parent) {
    particleSystemNode = new TNode(new TParticleSystem()); 
	parent -> addChild(this);
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