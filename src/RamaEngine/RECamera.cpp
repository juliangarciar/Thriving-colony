#include "RECamera.h"


RECamera::RECamera(TNode* parent) {
    rotationNode = new TNode(new TTransform(), parent);
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    cameraNode = new TNode(new TCamera(REEnums::CameraProjection::ProjectionPerspective, 0.3, 1000, 0, 480, 0, 640), scaleNode);
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

void RECamera::setFar(f32 f) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setFar(f);
}

void RECamera::setRight(f32 r) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setRight(r);
}

void RECamera::setLeft(f32 l) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setLeft(l);
}

void RECamera::setTop(f32 t) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setTop(t);
}

void RECamera::setBottom(f32 b) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setBottom(b);
}

void RECamera::setProjectionMode(REEnums::CameraProjection proj) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setProjection(proj);
}

void RECamera::setFov(f32 fov){
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setFov(fov);
}

void RECamera::setTargetPosition(f32 tX, f32 tY, f32 tZ) {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    c -> setTargetPosition(tX, tY, tZ);
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

f32 RECamera::getRight() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getRight();
}

f32 RECamera::getLeft() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getLeft();
}

f32 RECamera::getTop() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getTop();
}

f32 RECamera::getBottom() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getBottom();
}

REEnums::CameraProjection RECamera::getProjectionMode() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getProjection();
}

f32 RECamera::getFov() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getFov();
}

glm::mat4 RECamera::calculateViewMatrix() {
    // Sacar matriz camera
    TTransform* rt = (TTransform*) rotationNode -> getEntity();
    TTransform* tt = (TTransform*) translationNode -> getEntity();
    TTransform* st = (TTransform*) scaleNode -> getEntity();
    glm::mat4 cameraMatrix = rt ->getMatrix() * tt -> getMatrix() * st -> getMatrix();
    //Sacar posicion de la camara
    glm::vec4 v = glm::vec4(0,0,0,1) * cameraMatrix;
    glm::vec3 cameraPos = glm::vec3(v);
    // Posicion del objetivo
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    glm::vec3 tarPos = c -> getTargetPosition();
    
    glm::mat4 view = glm::lookAt(
        cameraPos,  
        tarPos, 
        glm::vec3(0,1,0) 
    );
    return view;
}

glm::mat4 RECamera::getProjectionMatrix() {
    TCamera* c = (TCamera*) cameraNode -> getEntity();
    return c -> getProjectionMatrix();
}

TNode* RECamera::getCameraNode() {
    return rotationNode;
}

TCamera* RECamera::getCameraEntity() {
    return (TCamera*) cameraNode -> getEntity();
}