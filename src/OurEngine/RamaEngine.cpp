#include "RamaEngine.h"

RamaEngine::RamaEngine() {
    sceneNode = new TNode();
}

RamaEngine::~RamaEngine() {
    delete sceneNode;
}

RELight* RamaEngine::createRELight() {
    return new RELight(sceneNode);
}

RECamera* RamaEngine::createRECamera() {
    return new RECamera(sceneNode);
}

REMesh* RamaEngine::createREMesh() {
    return new REMesh(sceneNode);
}

REAnimation* RamaEngine::createREAnimation() {
    return new REAnimation(sceneNode);
}

void RamaEngine::draw() {
    sceneNode -> draw();
}

TNode* RamaEngine::getSceneNode() {
    return sceneNode;
}
