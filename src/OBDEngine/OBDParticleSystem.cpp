#include "OBDParticleSystem.h"

OBDParticleSystem::OBDParticleSystem(OBDSceneNode* parent) : OBDEntity(parent) {
    //particleSystemNode = new TNode(new TParticle(), rotationNode); //ToDo 

	parent->addChild(this);
}

OBDParticleSystem::~OBDParticleSystem(){

}

void OBDParticleSystem::setParticleSize(glm::vec2){

}

void OBDParticleSystem::cleanParticles(){

}