#include "OBDCamera.h"


OBDCamera::OBDCamera(TNode* parent) {
    cameraNode = new TNode(new TCamera(OBDEnums::CameraProjection::ProjectionPerspective, 0.1, 1000, 0, 720, 0, 1280), parent); 
    //ToDo: esos parametros no deberian estar aqui
}

OBDCamera::~OBDCamera() {
    delete cameraNode;
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
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setActive(active);
}

void OBDCamera::setNearValue(f32 n) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setNear(n);
}

void OBDCamera::setFarValue(f32 f) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setFar(f);
}

void OBDCamera::setPerspectiveProjection() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setProjection(OBDEnums::CameraProjection::ProjectionPerspective);
}

void OBDCamera::setParallelProjection() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setProjection(OBDEnums::CameraProjection::ProjectionOrtographic);
}

void OBDCamera::setFov(f32 fov){
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setFov(fov);
}

bool OBDCamera::getActive() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getActive();
}

f32 OBDCamera::getNear() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getNear();
}

f32 OBDCamera::getFar() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getFar();
}

OBDEnums::CameraProjection OBDCamera::getProjectionMode() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getProjection();
}

f32 OBDCamera::getFov() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getFov();
}

glm::vec3 OBDCamera::getCameraPosition() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getCameraPosition();
}

glm::vec3 OBDCamera::getTargetPosition() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getTargetPosition();
}

TNode* OBDCamera::getCameraNode(){
    return cameraNode;
}

TCamera* OBDCamera::getCameraEntity(){
    return (TCamera*) cameraNode -> getEntity();
}