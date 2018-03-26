#include "RECamera.h"


RECamera::RECamera(TNode* parent) {
    cameraNode = new TNode(new TCamera(REEnums::CameraProjection::ProjectionPerspective, 0.1, 1000, 0, 720, 0, 1280), parent); 
    //ToDo: esos parametros no deberian estar aqui
}

RECamera::~RECamera() {
    delete cameraNode;
}

void RECamera::setTargetPosition(glm::vec3 p) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setTargetPosition(p);
}

void RECamera::setCameraPosition(glm::vec3 p) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setCameraPosition(p);
}

void RECamera::setActive(bool active) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setActive(active);
}

void RECamera::setNearValue(f32 n) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setNear(n);
}

void RECamera::setFarValue(f32 f) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setFar(f);
}

void RECamera::setPerspectiveProjection() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setProjection(REEnums::CameraProjection::ProjectionPerspective);
}

void RECamera::setParallelProjection() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setProjection(REEnums::CameraProjection::ProjectionOrtographic);
}

void RECamera::setFov(f32 fov){
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setFov(fov);
}

bool RECamera::getActive() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getActive();
}

f32 RECamera::getNear() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getNear();
}

f32 RECamera::getFar() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getFar();
}

REEnums::CameraProjection RECamera::getProjectionMode() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getProjection();
}

f32 RECamera::getFov() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getFov();
}

glm::vec3 RECamera::getCameraPosition() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getCameraPosition();
}

glm::vec3 RECamera::getTargetPosition() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getTargetPosition();
}

TNode* RECamera::getCameraNode(){
    return cameraNode;
}

TCamera* RECamera::getCameraEntity(){
    return (TCamera*) cameraNode -> getEntity();
}