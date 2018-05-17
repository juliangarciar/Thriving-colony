#include "OBDCamera.h"

OBDCamera::OBDCamera(OBDSceneNode* parent, i32 sW, i32 sH, f32 far, f32 fov) {
    cameraNode = new TNode(new TCamera(OBDEnums::CameraProjection::ProjectionPerspective, 0.1, far, 0, sH, 0, sW, fov));

    parent->addChild(cameraNode);
}

OBDCamera::~OBDCamera() {
    delete cameraNode;
    cameraNode = nullptr;
}

void OBDCamera::setTargetPosition(glm::vec3 p) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setTargetPosition(p);
}

void OBDCamera::setCameraPosition(glm::vec3 p) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setCameraPosition(p);
}

void OBDCamera::setActive(bool active) {
    cameraNode -> setActive(active);
}

void OBDCamera::setNearValue(f32 n) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setNear(n);
}

void OBDCamera::setFarValue(f32 f) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setFar(f);
}

void OBDCamera::setFov(f32 fov){
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setFov(fov);
}

void OBDCamera::setPerspectiveProjection() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setProjection(OBDEnums::CameraProjection::ProjectionPerspective);
}

void OBDCamera::setParallelProjection() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setProjection(OBDEnums::CameraProjection::ProjectionOrtographic);
}

bool OBDCamera::getActive() {
    return cameraNode -> getActive();
}

f32 OBDCamera::getNear() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getNear();
}

f32 OBDCamera::getFar() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getFar();
}

f32 OBDCamera::getFov() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getFov();
}

OBDEnums::CameraProjection OBDCamera::getProjectionMode() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getProjection();
}

glm::vec3 OBDCamera::getCameraPosition() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getCameraPosition();
}

glm::vec3 OBDCamera::getTargetPosition() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getTargetPosition();
}

TCamera* OBDCamera::getCameraEntity(){
    return (TCamera*) cameraNode -> getEntity();
}

TNode *OBDCamera::getFirstNode(){
    return cameraNode;
}