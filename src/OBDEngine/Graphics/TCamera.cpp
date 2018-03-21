#include "TCamera.h"

TCamera::TCamera(OBDEEnums::CameraProjection projectionMode, f32 n, f32 f, f32 t, f32 b, f32 l, f32 r, bool a) : TEntity(){
    active = a;

    setNear(n);
    setFar(f);
    
    setTop(t);
    setBottom(b);
    setLeft(l);
    setRight(r);

    setProjection(projectionMode);

    calculateViewMatrix();

    beginDraw();
}

TCamera::~TCamera(){

}

void TCamera::beginDraw(){
    if (active) {
        TMatrixCache *cache = TMatrixCache::Instance();
        cache->setMatrix(OBDEEnums::Matrices::MATRIX_PROJECTION, &pMat);
        cache->setMatrix(OBDEEnums::Matrices::MATRIX_VIEW, &vMat);
    }
}

void TCamera::endDraw(){

}

void TCamera::calculateViewMatrix() {
    vMat = glm::lookAt(
        cameraPosition,  
        targetPosition, 
        glm::vec3(0,1,0) 
    );
}

void TCamera::setTargetPosition(glm::vec3 p) {
    targetPosition = p;
    calculateViewMatrix();
}

glm::vec3 TCamera::getTargetPosition() {
    return targetPosition;
}

void TCamera::setCameraPosition(glm::vec3 p) {
    cameraPosition = p;
    calculateViewMatrix();
}

glm::vec3 TCamera::getCameraPosition() {
    return cameraPosition;
}

///////////////////////

void TCamera::setProjection(OBDEEnums::CameraProjection cp){
    projection = cp;
    if (cp == OBDEEnums::CameraProjection::ProjectionPerspective){
        // Calculate aspect ratio
        f32 width = right - left;
        f32 height = bottom - top;
        pMat = glm::perspective(/*fov*/glm::radians(45.0f), width / height, near, far);
    } else {
        pMat = glm::ortho(left, right, bottom, top, near, far);
    }
}

OBDEEnums::CameraProjection TCamera::getProjection(){
    return projection;
}

void TCamera::setActive(bool _active) {
    active = _active;
}

bool TCamera::getActive() {
    return active;
}

void TCamera::setFov(f32 f) {
    fov = f;
}

f32 TCamera::getFov() {
    return fov;
}

void TCamera::setNear(f32 n){
    near = n;
}

f32 TCamera::getNear(){
    return near;
}

void TCamera::setFar(f32 f){
    far = f;
}

f32 TCamera::getFar(){
    return far;
}

void TCamera::setTop(f32 t){
    top = t;
}

f32 TCamera::getTop(){
    return top;
}

void TCamera::setBottom(f32 b){
    bottom = b;
}

f32 TCamera::getBottom(){
    return bottom;
}

void TCamera::setLeft(f32 l){
    left = l;
}

f32 TCamera::getLeft(){
    return left;
}

void TCamera::setRight(f32 r){
    right = r;
}

f32 TCamera::getRight(){
    return right;
}