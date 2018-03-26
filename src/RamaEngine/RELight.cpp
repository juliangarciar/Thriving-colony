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

void RELight::setAmbientColor(REColor c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    ambientColor = c;
    l -> setAmbientComponent(ambientColor, ambientIntensity);
}

REColor RELight::getAmbientColor() {
    return ambientColor;
}

void RELight::setAmbientIntensity(u32 c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    ambientIntensity = c;
    l -> setAmbientComponent(ambientColor, ambientIntensity);
}

u32 RELight::getAmbientIntensity() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return ambientIntensity;
}

void RELight::setDiffuseColor(REColor c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    diffuseColor = c;
    l -> setDiffuseComponent(diffuseColor, diffuseIntensity);
}

REColor RELight::getDiffuseColor() {
    return diffuseColor;
}

void RELight::setDiffuseIntensity(u32 c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    diffuseIntensity = c;
    l -> setDiffuseComponent(diffuseColor, diffuseIntensity);
}

u32 RELight::getDiffuseIntensity() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return diffuseIntensity;
}

void RELight::setSpecularColor(REColor c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    specularColor = c;
    l -> setSpecularComponent(specularColor, specularIntensity);
}

REColor RELight::getSpecularColor() {
    return specularColor;
}

void RELight::setSpecularIntensity(u32 c) {
    TLight* l = (TLight*) lightNode -> getEntity();
    specularIntensity = c;
    l -> setSpecularComponent(specularColor, specularIntensity);
}

u32 RELight::getSpecularIntensity() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return specularIntensity;
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