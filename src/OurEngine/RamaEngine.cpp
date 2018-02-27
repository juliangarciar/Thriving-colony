#include "RamaEngine.h"

RamaEngine::RamaEngine() {
    rootNode = new TNode();
    // Registers
    cameras = new std::vector<TNode*>();
    lights = new std::vector<TNode*>();
    sceneNodes = new std::vector<TNode*>();
    // Create default layer
    createRESceneNode();
}

RamaEngine::~RamaEngine() {
    delete rootNode;
    delete defaultLayer;
    cameras -> clear();
    delete cameras;
    lights -> clear();
    delete lights;
    sceneNodes -> clear();
    delete sceneNodes;
}

RELight* RamaEngine::createRELight() {
    RELight* rel = new RELight(sceneNodes ->at(0));
    registerLight(rel -> getLightNode());
    return rel;
}

RELight* RamaEngine::createRELight(RESceneNode* layer) {
    RELight* rel = new RELight(layer -> getSceneNode());
    registerLight(rel -> getLightNode());
    return rel;
}

RECamera* RamaEngine::createRECamera() {
    RECamera* rec = new RECamera(sceneNodes ->at(0));
    registerCamera(rec -> getCameraNode());
    return rec;
}

RECamera* RamaEngine::createRECamera(RESceneNode* layer) {
    RECamera* rec = new RECamera(layer -> getSceneNode());
    registerCamera(rec -> getCameraNode());
    return rec;
}

REMesh* RamaEngine::createREMesh() {
    return new REMesh(rootNode);
}

REMesh* RamaEngine::createREMesh(RESceneNode* layer) {
    return new REMesh(layer -> getSceneNode());
}

REAnimation* RamaEngine::createREAnimation() {
    return new REAnimation(rootNode);
}

REAnimation* RamaEngine::createREAnimation(RESceneNode* layer) {
    return new REAnimation(layer -> getSceneNode());
}

RESceneNode* RamaEngine::createRESceneNode() {
    RESceneNode* resn = new RESceneNode(rootNode);
    registerSceneNode(resn ->getSceneNode());
    return resn;
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

void RamaEngine::registerCamera(TNode* cameraNode) {
    cameras -> push_back(cameraNode);
}

void RamaEngine::registerLight(TNode* lightNode) {
    lights -> push_back(lightNode);
}

void RamaEngine::registerSceneNode(TNode* sceneNode) {
    sceneNodes -> push_back(sceneNode);
}