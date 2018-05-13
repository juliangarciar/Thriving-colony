#include "OBDLight.h"

OBDLight::OBDLight(OBDColor color, u32 intensity) {
    lightNode = new TNode(new TLight(color, intensity));
}

OBDLight::OBDLight(OBDSceneNode* parent, OBDColor color, u32 intensity) {
    lightNode = new TNode(new TLight(color, intensity));

    parent->addChild(this);
}

OBDLight::~OBDLight() {
    delete lightNode;
    lightNode = nullptr;
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
    lightNode -> setActive(active);
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setActive(active);
}

bool OBDLight::getActive() {
    return lightNode -> getActive();
}

void OBDLight::setPosition(glm::vec3 p) {
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setPosition(p);
}

glm::vec3 OBDLight::getPosition() {
    TLight* l = (TLight*) lightNode -> getEntity();
    return l -> getPosition();
}

TLight* OBDLight::getLightEntity() {
    return (TLight*) lightNode -> getEntity();
}

TNode *OBDLight::getFirstNode(){
    return lightNode;
}

void OBDLight::setType(OBDEnums::LightTypes newType) {
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setType(newType);
}