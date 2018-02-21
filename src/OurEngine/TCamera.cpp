#include "TCamera.h"


TCamera::TCamera(TEnums::CameraProjection projectionMode, f32 n, f32 f, f32 t, f32 b, f32 l, f32 r) : TEntity(){
    setNear(n);
    setFar(f);
    setProjection(projectionMode);

    setTop(t);
    setBottom(b);
    setLeft(l);
    setRight(r);

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

void TCamera::setPerspective(f32 n, f32 f, f32 t, f32 b, f32 l, f32 r){
    setNear(n);
    setFar(f);
    setProjection(TEnums::CameraProjection::ProjectionPerspective);

    setTop(t);
    setBottom(b);
    setRight(r);
    setLeft(l);
    // Calculate aspect ratio
    f32 width = r - l;
    f32 height = b - t;
    projectionMatrix = glm::perspective(fov, width / height, n, f);
}

void TCamera::setParallel(f32, f32, f32, f32, f32, f32){
    //ToDo: Angela
}

void TCamera::setProjection(TEnums::CameraProjection cp){
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

void TCamera::setRight(f32 r){
    right = r;
}

TEnums::CameraProjection TCamera::getProjection(){
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