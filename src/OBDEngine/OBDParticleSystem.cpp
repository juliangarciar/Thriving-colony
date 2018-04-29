#include "OBDParticleSystem.h"

OBDParticleSystem::OBDParticleSystem() {

}

OBDParticleSystem::OBDParticleSystem(OBDSceneNode* parent, i32 id, glm::vec3 pos) {
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    
    ID = id;

    parent -> addChild(this);
}