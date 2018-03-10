#include "TCamera.h"

TCamera::TCamera(REEnums::CameraProjection projectionMode, f32 n, f32 f, f32 t, f32 b, f32 l, f32 r, bool a) : TEntity(){
    setNear(n);
    setFar(f);
    setProjection(projectionMode);

    setTop(t);
    setBottom(b);
    setLeft(l);
    setRight(r);

    active = a;

    projectionMatrix = glm::mat4(1.0f);
}

TCamera::~TCamera(){

}

void TCamera::beginDraw(){
    if (active) {
        viewMatrix = glm::inverse(modelMatrix);
    }
}

void TCamera::endDraw(){

}

void TCamera::setPerspective(){
    setProjection(REEnums::CameraProjection::ProjectionPerspective);
    // Calculate aspect ratio
    f32 width = right - left;
    f32 height = bottom - top;
    projectionMatrix = glm::perspective(fov, width / height, near, far);
}

void TCamera::setParallel(f32, f32, f32, f32, f32, f32){
    //ToDo: tito juli
}

void TCamera::setProjection(REEnums::CameraProjection cp){
    projection = cp;
}

void TCamera::setActive(bool _active) {
    active = _active;
}

void TCamera::setNear(f32 n){
    near = n;
}

void TCamera::setFar(f32 f){
    far = f;
}

void TCamera::setFov(f32 f) {
    fov = f;
}

void TCamera::setTop(f32 t){
    top = t;
}

void TCamera::setBottom(f32 b){
    bottom = b;
}

void TCamera::setLeft(f32 l){
    left = l;
}

void TCamera::setTargetPosition(f32 tX, f32 tY, f32 tZ) {
    targetPosition = glm::vec3(tX, tY, tZ);
}

void TCamera::setRight(f32 r){
    right = r;
}

REEnums::CameraProjection TCamera::getProjection(){
    return projection;
}

bool TCamera::getActive() {
    return active;
}

f32 TCamera::getNear(){
    return near;
}

f32 TCamera::getFar(){
    return far;
}

f32 TCamera::getFov() {
    return fov;
}

f32 TCamera::getTop(){
    return top;
}

f32 TCamera::getBottom(){
    return bottom;
}

f32 TCamera::getLeft(){
    return left;
}

f32 TCamera::getRight(){
    return right;
}

glm::mat4 TCamera::getViewMatrix() {
    return viewMatrix;
}

glm::mat4 TCamera::getProjectionMatrix() {
    return projectionMatrix;
}

glm::vec3 TCamera::getTargetPosition() {
    return targetPosition;
}