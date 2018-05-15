#include "OBDParticleSystem.h"

OBDParticleSystem::OBDParticleSystem() {

}

OBDParticleSystem::OBDParticleSystem(OBDSceneNode* parent, i32 id, glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale) {
    rotationNode = new TNode(new TTransform());
    TTransform* aux = (TTransform*)(rotationNode -> getEntity());
    aux -> rotate(rotation.x, rotation.y, rotation.z, 0);
    translationNode = new TNode(new TTransform(), rotationNode);
    aux = (TTransform*)(translationNode -> getEntity());
    aux -> translate(pos.x, pos.y, pos.z);
    scaleNode = new TNode(new TTransform(), translationNode);
    aux = (TTransform*)(scaleNode -> getEntity());
    aux -> scale(scale.x, scale.y, scale.z);
    
    ID = id;

    parent -> addChild(this);
}

OBDParticleSystem::~OBDParticleSystem() {
    /*delete emiter;
    for (i32 i = 0; i < affectors.size(); i++) {
        delete affectors[i];
    }
    affectors.clear();
    delete particleSystemNode;
    delete rotationNode;
    delete translationNode;
    delete scaleNode;*/
}

void OBDParticleSystem::setEmiter(OBDParticleEmiter* newEmiter) {
    /*delete emiter;
    emiter = newEmiter;*/
}

void OBDParticleSystem::addAffector(OBDParticleAffector* newAffector) {
    affectors.push_back(newAffector);
}

void OBDParticleSystem::cleanEmiters() {
    /*for (i32 i = 0; i < emiters.size(); i++) {
        delete emiters[i];
    }
    emiters.clear();*/
}

void OBDParticleSystem::cleanAffectors() {
    /*for (i32 i = 0; i < affectors.size(); i++) {
        delete affectors[i];
    }
    affectors.clear();*/
}

TNode* OBDParticleSystem::getFirstNode() {
    return particleSystemNode;
}