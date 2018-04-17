#include "OBDLight.h"

OBDLight::OBDLight(OBDColor color, u32 intensity) {
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    lightNode = new TNode(new TLight(color, intensity), scaleNode);
}

OBDLight::OBDLight(TNode* parent, OBDColor color, u32 intensity) {
    rotationNode = new TNode(new TTransform(), parent);
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    lightNode = new TNode(new TLight(color, intensity), scaleNode);
}

OBDLight::~OBDLight() {
    delete rotationNode;
    delete translationNode;
    delete scaleNode;
    delete lightNode;
}

void OBDLight::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
}

void OBDLight::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
}

void OBDLight::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
}

void OBDLight::setAmbientColor(OBDColor c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    ambientColor = c;
    l -> setAmbientComponent(ambientColor, ambientIntensity);
}

OBDColor OBDLight::getAmbientColor() {
    return ambientColor;
}

void OBDLight::setAmbientIntensity(u32 c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    ambientIntensity = c;
    l -> setAmbientComponent(ambientColor, ambientIntensity);
}

u32 OBDLight::getAmbientIntensity() {
    return ambientIntensity;
}

void OBDLight::setDiffuseColor(OBDColor c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    diffuseColor = c;
    l -> setDiffuseComponent(diffuseColor, diffuseIntensity);
}

OBDColor OBDLight::getDiffuseColor() {
    return diffuseColor;
}

void OBDLight::setDiffuseIntensity(u32 c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    diffuseIntensity = c;
    l -> setDiffuseComponent(diffuseColor, diffuseIntensity);
}

u32 OBDLight::getDiffuseIntensity() {
    return diffuseIntensity;
}

void OBDLight::setSpecularColor(OBDColor c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    specularColor = c;
    l -> setSpecularComponent(specularColor, specularIntensity);
}

OBDColor OBDLight::getSpecularColor() {
    return specularColor;
}

void OBDLight::setSpecularIntensity(u32 c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    specularIntensity = c;
    l -> setSpecularComponent(specularColor, specularIntensity);
}

u32 OBDLight::getSpecularIntensity() {
    return specularIntensity;
}

void OBDLight::setActive(bool active) {
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setActive(active);
}

bool OBDLight::getActive() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return l -> getActive();
}

TNode* OBDLight::getLightNode() {
    return rotationNode;
}

TLight* OBDLight::getLightEntity() {
    return (TLight*) lightNode -> getEntity();
}

void OBDLight::setPosition(glm::vec3 p) {
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setPosition(p);
}

glm::vec3 OBDLight::getPosition() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return l -> getPosition();
}

void OBDLight::setRotation(glm::vec3 r, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(r.x, r.y, r.z, angle);
}

void OBDLight::setScale(glm::vec3 s) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(s.x, s.y, s.z);
}