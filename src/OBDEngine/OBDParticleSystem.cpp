#include "OBDParticleSystem.h"

OBDParticleSystem::OBDParticleSystem(OBDSceneNode* parent) : OBDEntity(parent) {
    //particleSystemNode = new TNode(new TParticle(), rotationNode); //ToDo 

	parent->addChild(this);
}

OBDParticleSystem::~OBDParticleSystem() {
    for (i32 i = 0; i < emiters.size(); i++) {
        delete emiters[i];
    }
    emiters.clear();
    for (i32 i = 0; i < affectors.size(); i++) {
        delete affectors[i];
    }
    affectors.clear();
}

void OBDParticleSystem::setEmiter(OBDParticleEmiter* newEmiter) {
    //delete emiter;
    //emiter = newEmiter;
}

void OBDParticleSystem::addAffector(OBDParticleAffector* newAffector) {
    affectors.push_back(newAffector);
}

void OBDParticleSystem::cleanEmiters() {
    for (i32 i = 0; i < emiters.size(); i++) {
        delete emiters[i];
    }
    emiters.clear();
}

void OBDParticleSystem::cleanAffectors() {
    for (i32 i = 0; i < affectors.size(); i++) {
        delete affectors[i];
    }
    affectors.clear();
}