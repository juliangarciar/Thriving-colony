#include "OBDSceneNode.h"

OBDSceneNode::OBDSceneNode() {
	node_position = glm::vec3(0);
	node_rotation = glm::vec3(0);
	node_scale = glm::vec3(0);

    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
}

OBDSceneNode::OBDSceneNode(TNode* parent) {
	node_position = glm::vec3(0);
	node_rotation = glm::vec3(0);
	node_scale = glm::vec3(0);

    rotationNode = new TNode(new TTransform(), parent);
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
}

OBDSceneNode::OBDSceneNode(OBDSceneNode* parent) {
	node_position = glm::vec3(0);
	node_rotation = glm::vec3(0);
	node_scale = glm::vec3(0);
	
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);

    parent->addChild(this);
}

OBDSceneNode::~OBDSceneNode() {
    delete rotationNode;
    delete translationNode;
    delete scaleNode;
}

void OBDSceneNode::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
    node_position += glm::vec3(tX, tY, tZ);
}

void OBDSceneNode::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
    node_rotation += glm::vec3(rX, rY, rZ);
}

void OBDSceneNode::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
    node_scale += glm::vec3(sX, sY, sZ);
}

void OBDSceneNode::setPosition(glm::vec3 p) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    glm::vec3 o = node_position - p;
    t -> translate(o.x, o.y, o.z);
    node_position = p;
}

void OBDSceneNode::setRotation(glm::vec3 r, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    glm::vec3 o = node_rotation - r;
    t -> rotate(o.x, o.y, o.z, angle);
    node_rotation = r;
}

void OBDSceneNode::setScale(glm::vec3 s) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    glm::vec3 o = node_scale - s;
    t -> scale(o.x, o.y, o.z);
    node_scale = s;
}

void OBDSceneNode::addChild(OBDEntity *e){
    e->getFirstNode()->setParent(scaleNode);
    scaleNode->addChild(e->getFirstNode());
}

void OBDSceneNode::addChild(TNode *e){
    e->setParent(scaleNode);
    scaleNode->addChild(e);
}

TNode* OBDSceneNode::getFirstNode() {
    return rotationNode;
}