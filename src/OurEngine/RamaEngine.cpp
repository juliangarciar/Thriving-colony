#include "RamaEngine.h"

RamaEngine::RamaEngine() {
    rootNode = new TNode();
}

RamaEngine::~RamaEngine() {
    delete rootNode;
}

RELight* RamaEngine::createRELight() {
    return new RELight(rootNode);
}

RECamera* RamaEngine::createRECamera() {
    return new RECamera(rootNode);
}

REMesh* RamaEngine::createREMesh() {
    return new REMesh(rootNode);
}

REAnimation* RamaEngine::createREAnimation() {
    return new REAnimation(rootNode);
}

RESceneNode* RamaEngine::createRESceneNode() {
    return new RESceneNode(rootNode);
}

void RamaEngine::draw() {
    rootNode -> draw();
}

TNode* RamaEngine::getRootNode() {
    return rootNode;
}

RESceneNode* RamaEngine::getDefaultLayer() {
    return defaultLayer;
}
