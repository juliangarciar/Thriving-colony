#include "OBDLight.h"

OBDLight::OBDLight(OBDColor color, f32 intensity, f32 ambient, f32 attenuation) {
    lightNode = new TNode(new TLight(color, intensity, ambient, attenuation));
}

OBDLight::OBDLight(OBDSceneNode* parent, OBDColor color, f32 intensity, f32 ambient, f32 attenuation) {
    lightNode = new TNode(new TLight(color, intensity, ambient, attenuation));

    parent->addChild(this);
}

OBDLight::~OBDLight() {
    delete lightNode;
    lightNode = nullptr;
}

void OBDLight::setColor(OBDColor color, f32 intensity){
    TLight* l = (TLight*) lightNode -> getEntity();
    l -> setColor(color, intensity);
}

void OBDLight::setAmbientCoeficient(f32 am){
    TLight* l = (TLight*) lightNode -> getEntity();
	l -> setAmbientCoeficient(am);
}

void OBDLight::setAttenuationCoeficient(f32 at){
    TLight* l = (TLight*) lightNode -> getEntity();
	l -> setAttenuationCoeficient(at);
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