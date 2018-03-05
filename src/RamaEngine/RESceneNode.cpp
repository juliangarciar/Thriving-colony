#include "RESceneNode.h"

RESceneNode::RESceneNode(TNode* parent) {
    rotationNode = new TNode(new TTransform(), parent);
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    sceneNode = new TNode();
    // o esto o getcameraNode
    //RamaEngine::Instance() -> registerSceneNode(sceneNode);
}

RESceneNode::~RESceneNode() {
    delete rotationNode;
    delete translationNode;
    delete scaleNode;
    delete sceneNode;
}

void RESceneNode::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
}

void RESceneNode::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
}

void RESceneNode::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
}

TNode* RESceneNode::getSceneNode() {
    return sceneNode;
}