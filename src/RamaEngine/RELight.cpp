#include "RELight.h"

RELight::RELight(REColor color, u32 intensity) {
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    lightNode = new TNode(new TLight(color, intensity), scaleNode);
}

RELight::RELight(TNode* parent, REColor color, u32 intensity) {
    rotationNode = new TNode(new TTransform(), parent);
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    lightNode = new TNode(new TLight(color, intensity), scaleNode);
}

RELight::~RELight() {
    delete rotationNode;
    delete translationNode;
    delete scaleNode;
    delete lightNode;
}

void RELight::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
}

void RELight::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
}

void RELight::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
}

void RELight::setColor(REColor c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setColor(c);
}

REColor RELight::getColor() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return l -> getColor();
}

void RELight::setIntensity(u32 c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setIntensity(c);
}

u32 RELight::getIntensity() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return l -> getIntensity();
}

void RELight::setActive(bool active) {
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setActive(active);
}

bool RELight::getActive() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return l -> getActive();
}

TNode* RELight::getLightNode() {
    return rotationNode;
}

TLight* RELight::getLightEntity() {
    return (TLight*) lightNode -> getEntity();
}

void RELight::setPosition(glm::vec3 p) {
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setPosition(p);
}

glm::vec3 RELight::getPosition() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return l -> getPosition();
}