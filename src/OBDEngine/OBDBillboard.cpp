#include "OBDBillboard.h"

OBDBillboard::OBDBillboard() {

}

OBDBillboard::OBDBillboard(OBDSceneNode* parent, i32 id, glm::vec3 pos, GLuint shader) {
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    
    ID = id;

    billboardNode = new TNode(new TBillboard(pos, shader));

    parent -> addChild(this);
}

OBDBillboard::~OBDBillboard() {
    delete billboardNode;
    delete rotationNode;
    delete translationNode;
    delete scaleNode;
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

i32 OBDBillboard::getID() {
    return ID;
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

TNode *OBDBillboard::getFirstNode() {
    return billboardNode;
}
