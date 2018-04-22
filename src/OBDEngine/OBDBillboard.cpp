#include "OBDBillboard.h"

OBDBillboard::OBDBillboard() {

}

OBDBillboard::OBDBillboard(OBDSceneNode* parent, i32 id, Vector3<f32> positionData) {
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    
    ID = id;
    position = positionData;

    billboardNode = new TNode(new TBillboard(position.x, position.y, position.z));

    parent -> addChild(this);
}

TNode *OBDBillboard::getFirstNode() {
    return billboardNode;
}

void OBDBillboard::setColor(OBDColor* newTopColor, OBDColor* newBottomColor) {
    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
    aux -> setColor(newTopColor, newBottomColor);
}