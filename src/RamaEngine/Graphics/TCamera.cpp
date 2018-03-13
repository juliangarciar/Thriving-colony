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
        glm::vec3 cameraPos = glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z);
        glm::vec3 tarPos = glm::vec3(targetPosition.x, targetPosition.y, targetPosition.z);
        viewMatrix = glm::lookAt(
            cameraPos,  
            tarPos, 
            glm::vec3(0,1,0) 
        );
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

void TCamera::setParallel(){
    /* I think is done */
    setProjection(REEnums::CameraProjection::ProjectionParallel);
    projectionMatrix = glm::ortho(left, right, bottom, top, near, far);

}

void TCamera::setTargetPosition(glm::vec3 p) {
    targetPosition = p;
}

glm::vec3 TCamera::getTargetPosition() {
    return targetPosition;
}

void TCamera::setCameraPosition(glm::vec3 p) {
    cameraPosition = p;
}

glm::vec3 TCamera::getCameraPosition() {
    return cameraPosition;
}

bool TCamera::getActive() {
    return active;
}

void TCamera::setActive(bool _active) {
    active = _active;
}

f32 TCamera::getFov() {
    return fov;
}

void TCamera::setFov(f32 f) {
    fov = f;
}

f32 TCamera::getNear(){
    return near;
}

void TCamera::setNear(f32 n){
    near = n;
}

f32 TCamera::getFar(){
    return far;
}

void TCamera::setFar(f32 f){
    far = f;
}
///////////////////////

void TCamera::setProjection(REEnums::CameraProjection cp){
    projection = cp;
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

REEnums::CameraProjection TCamera::getProjection(){
    return projection;
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

//ToDo
glm::vec3 getTargetPosition(){
    return glm::vec3();
}

//ToDo
glm::vec3 getCameraPosition(){
    return glm::vec3();
}