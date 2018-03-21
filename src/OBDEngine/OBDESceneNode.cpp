#include "OBDESceneNode.h"

OBDESceneNode::OBDESceneNode(TNode* parent) {
    rotationNode = new TNode(new TTransform(), parent);
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    sceneNode = scaleNode;
    // o esto o getcameraNode
    //OBDEngine::Instance() -> registerSceneNode(sceneNode);
}

OBDESceneNode::OBDESceneNode(OBDESceneNode* parent) {
    rotationNode = new TNode(new TTransform(), parent->getSceneNode());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    sceneNode = scaleNode;
    // o esto o getcameraNode
    //OBDEngine::Instance() -> registerSceneNode(sceneNode);
}

OBDESceneNode::~OBDESceneNode() {
    delete rotationNode;
    delete translationNode;
    delete scaleNode;
}

void OBDESceneNode::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
}

void OBDESceneNode::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
}

void OBDESceneNode::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
}

TNode* OBDESceneNode::getSceneNode() {
    return sceneNode;
}