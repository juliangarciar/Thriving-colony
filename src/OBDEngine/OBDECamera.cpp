#include "OBDECamera.h"


OBDECamera::OBDECamera(TNode* parent) {
    rotationNode = new TNode(new TTransform(), parent);
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    cameraNode = new TNode(new TCamera(OBDEEnums::CameraProjection::ProjectionPerspective, 0.1, 1000, 0, 480, 0, 640), scaleNode); 
    //ToDo: esos parametros no deberian estar aqui
}

OBDECamera::~OBDECamera() {
    delete rotationNode;
    delete translationNode;
    delete scaleNode;
    delete cameraNode;
}

void OBDECamera::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
}

void OBDECamera::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
}

void OBDECamera::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
}

void OBDECamera::setActive(bool active) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setActive(active);
}

void OBDECamera::setNear(f32 n) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setNear(n);
}

void OBDECamera::setPerspectiveProjection() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setProjection(OBDEEnums::CameraProjection::ProjectionPerspective);
}

void OBDECamera::setParallelProjection() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setProjection(OBDEEnums::CameraProjection::ProjectionOrtographic);
}

void OBDECamera::setFarValue(f32 f) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setFar(f);
}

void OBDECamera::setFov(f32 fov){
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setFov(fov);
}

void OBDECamera::setTargetPosition(glm::vec3 p) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setTargetPosition(p);
}

void OBDECamera::setCameraPosition(glm::vec3 p) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setCameraPosition(p);
}

bool OBDECamera::getActive() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getActive();
}

f32 OBDECamera::getNear() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getNear();
}

f32 OBDECamera::getFar() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getFar();
}

OBDEEnums::CameraProjection OBDECamera::getProjectionMode() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getProjection();
}

f32 OBDECamera::getFov() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getFov();
}

glm::vec3 OBDECamera::getCameraPosition() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getCameraPosition();
}

glm::vec3 OBDECamera::getTargetPosition() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getTargetPosition();
}

TNode* OBDECamera::getCameraNode(){
    return rotationNode;
}

TCamera* OBDECamera::getCameraEntity(){
    return (TCamera*) cameraNode -> getEntity();
}