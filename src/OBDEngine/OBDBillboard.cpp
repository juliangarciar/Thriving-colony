#include "OBDBillboard.h"

//OBDBillboard::OBDBillboard() {
//
//}
//
//OBDBillboard::OBDBillboard(OBDSceneNode* parent, i32 id, Vector3<f32> positionData) {
//    rotationNode = new TNode(new TTransform());
//    translationNode = new TNode(new TTransform(), rotationNode);
//    scaleNode = new TNode(new TTransform(), translationNode);
//    
//    ID = id;
//    position = positionData;
//
//    billboardNode = new TNode(new TBillboard(position.x, position.y, position.z));
//
//    parent -> addChild(this);
//}
//
//TNode *OBDBillboard::getFirstNode() {
//    return billboardNode;
//}
//
//void OBDBillboard::setPosition(Vector3<f32> pos) {
//    position = pos;
//    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
//    aux -> setPosition(pos.x, pos.y, pos.z);
//}
//
//void OBDBillboard::setColor(OBDColor* newTopColor, OBDColor* newBottomColor) {
//    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
//    aux -> setColor(newTopColor, newBottomColor);
//}
//
//Vector3<f32> OBDBillboard::getPosition() {
//    return position;
//}
//
//i32 OBDBillboard::getID() {
//    return ID;
//}
//
//OBDColor* OBDBillboard::getTopColor() {
//    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
//    return aux -> getTopColor();
//}
//
//OBDColor* OBDBillboard::getBottomColor() {
//    TBillboard* aux = (TBillboard*)(billboardNode -> getEntity());
//    return aux -> getBottomColor();
//}