#include "OBDELight.h"

OBDELight::OBDELight(OBDEColor color, u32 intensity) {
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    lightNode = new TNode(new TLight(color, intensity), scaleNode);
}

OBDELight::OBDELight(TNode* parent, OBDEColor color, u32 intensity) {
    rotationNode = new TNode(new TTransform(), parent);
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    lightNode = new TNode(new TLight(color, intensity), scaleNode);
}

OBDELight::~OBDELight() {
    delete rotationNode;
    delete translationNode;
    delete scaleNode;
    delete lightNode;
}

void OBDELight::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
}

void OBDELight::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
}

void OBDELight::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
}

void OBDELight::setColor(OBDEColor c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setColor(c);
}

OBDEColor OBDELight::getColor() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return l -> getColor();
}

void OBDELight::setIntensity(u32 c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setIntensity(c);
}

u32 OBDELight::getIntensity() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return l -> getIntensity();
}

void OBDELight::setActive(bool active) {
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setActive(active);
}

bool OBDELight::getActive() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return l -> getActive();
}

TNode* OBDELight::getLightNode() {
    return rotationNode;
}

TLight* OBDELight::getLightEntity() {
    return (TLight*) lightNode -> getEntity();
}