#include "RECamera.h"


RECamera::RECamera(TNode* parent) {
    rotationNode = new TNode(new TTransform(), parent);
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    cameraNode = new TNode(new TCamera(TEnums::CameraProjection::ProjectionPerspective, 0.3, 1000, 0, 480, 0, 640), scaleNode);
}

RECamera::~RECamera() {
    delete rotationNode;
    delete translationNode;
    delete scaleNode;
    delete cameraNode;
}

//ToDo: arreglar el casteo
void RECamera::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    //rotationNode -> (TTransform)getEntity() -> rotate(rX, rY, rZ, angle);
}

void RECamera::scale(f32 sX, f32 sY, f32 sZ) {
    //scaleNode -> (TTransform)getEntity() -> scale(sX, sY, sZ);
}

void RECamera::translate(f32 tX, f32 tY, f32 tZ) {
    //translationNode -> (TTransform)getEntity() -> translate(tX, tY, tZ);
}