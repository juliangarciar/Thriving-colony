#include "OBDBillboard.h"
#include "../GraphicEngine/Window.h"

OBDBillboard::OBDBillboard(OBDSceneNode* parent, OBDShaderProgram *sP, glm::vec3 position, glm::vec2 size) {
    billboardNode = new TNode(new TBillboard(sP->getShaderProgram(), position, size));
	parent -> addChild(billboardNode);
}

OBDBillboard::~OBDBillboard(){
	delete billboardNode;
	billboardNode = nullptr;
}

void OBDBillboard::setPosition(glm::vec3 pos) {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    aux -> setPosition(pos);
}

void OBDBillboard::setColor(OBDColor newBackColor, OBDColor newFrontColor) {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    aux -> setColor(newBackColor, newFrontColor);
}

void OBDBillboard::setSize(glm::vec2 s) {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    aux -> setSize(s);
}

void OBDBillboard::setFrontWidth(f32 s) {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    aux -> setFrontWidth(s);
}

void OBDBillboard::setActive(bool a){
	billboardNode -> setActive(a);
}

glm::vec3 OBDBillboard::getPosition() {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    return aux -> getPosition();
}

glm::vec2 OBDBillboard::getSize() {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    return aux -> getSize();
}

f32 OBDBillboard::getFrontWidth() {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    return aux -> getFrontWidth();
}