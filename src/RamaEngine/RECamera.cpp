#include "RECamera.h"


RECamera::RECamera(TNode* parent) {
    rotationNode = new TNode(new TTransform(), parent);
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    cameraNode = new TNode(new TCamera(REEnums::CameraProjection::ProjectionPerspective, 0.1, 1000, 0, 480, 0, 640), scaleNode);
    // o esto o getcameraNode
}

RECamera::~RECamera() {
    delete rotationNode;
    delete translationNode;
    delete scaleNode;
    delete cameraNode;
}

void RECamera::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
}

void RECamera::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
}

void RECamera::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
}

void RECamera::setActive(bool active) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setActive(active);
}

void RECamera::setNear(f32 n) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setNear(n);
}

void RECamera::setPerspectiveProjection() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setProjection(REEnums::CameraProjection::ProjectionPerspective);
}

void RECamera::setParallelProjection() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setProjection(REEnums::CameraProjection::ProjectionOrtographic);
}

void RECamera::setFarValue(f32 f) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setFar(f);
}

void RECamera::setFov(f32 fov){
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setFov(fov);
}

void RECamera::setTargetPosition(glm::vec3 p) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setTargetPosition(p);
}

void RECamera::setCameraPosition(glm::vec3 p) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setCameraPosition(p);
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
    return rotationNode;
}

TCamera* RECamera::getCameraEntity(){
    return (TCamera*) cameraNode -> getEntity();
}