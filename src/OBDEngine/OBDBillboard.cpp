#include "OBDBillboard.h"

OBDBillboard::OBDBillboard(OBDSceneNode* parent, glm::vec3 position, GLuint shaderID) {
    billboardNode = new TNode(new TBillboard(position, shaderID));

	parent->addChild(billboardNode);
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

void OBDBillboard::setBottomWidth(f32 newBottomWidth) {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    aux -> setSize(-1, -1, newBottomWidth);
}

glm::vec3 OBDBillboard::getPosition() {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    return aux -> getPosition();
}

OBDColor* OBDBillboard::getTopColor() {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    return aux -> getTopColor();
}

OBDColor* OBDBillboard::getBottomColor() {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    return aux -> getBottomColor();
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