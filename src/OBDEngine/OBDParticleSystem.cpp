#include "OBDParticleSystem.h"

OBDParticleSystem::OBDParticleSystem() {

}

OBDParticleSystem::OBDParticleSystem(OBDSceneNode* parent, i32 id, glm::vec3 pos, glm::vec3 rotation, glm::vec3 scale) {
    rotationNode = new TNode(new TTransform());
    TTransform* aux = (TTransform*)(rotationNode -> getEntity());
    aux -> rotate(rotation.x, rotation.y, rotation.z);
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    
    ID = id;

    parent -> addChild(this);
}