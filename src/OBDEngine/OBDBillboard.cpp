#include "OBDBillboard.h"

OBDBillboard::OBDBillboard(OBDSceneNode* parent, glm::vec3 position, OBDShaderProgram *s) {
	shader = s;
    billboardNode = new TNode(new TBillboard(position, shader->getShaderProgram()));
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

void OBDBillboard::setColor(OBDColor* newTopColor, OBDColor* newBottomColor) {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    aux -> setColor(newTopColor, newBottomColor);
}

void OBDBillboard::setSize(f32 newHeight, f32 newTopWidth, f32 newBottomWidth) {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    aux -> setSize(newHeight, newTopWidth, newBottomWidth);
}

glm::vec3 OBDBillboard::getPosition() {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    return aux -> getPosition();
}

f32 OBDBillboard::getHeight() {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    return aux -> getHeight();
}

f32 OBDBillboard::getTopWidth() {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    return aux -> getTopWidth();
}

f32 OBDBillboard::getBottomWidth() {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    return aux -> getBottomWidth();
}