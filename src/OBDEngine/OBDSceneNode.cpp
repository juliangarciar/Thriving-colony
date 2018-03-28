#include "OBDSceneNode.h"

OBDSceneNode::OBDSceneNode(TNode* parent) {
    rotationNode = new TNode(new TTransform(), parent);
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    sceneNode = scaleNode;
    // o esto o getcameraNode
    //OBDEngine::Instance() -> registerSceneNode(sceneNode);
}

OBDSceneNode::OBDSceneNode(OBDSceneNode* parent) {
    rotationNode = new TNode(new TTransform(), parent->getSceneNode());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    sceneNode = scaleNode;
    // o esto o getcameraNode
    //OBDEngine::Instance() -> registerSceneNode(sceneNode);
}

OBDSceneNode::~OBDSceneNode() {
    delete rotationNode;
    delete translationNode;
    delete scaleNode;
}

void OBDSceneNode::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
}

void OBDSceneNode::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
}

void OBDSceneNode::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
}

TNode* OBDSceneNode::getSceneNode() {
    return sceneNode;
}