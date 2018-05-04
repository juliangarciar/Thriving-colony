#include "TCamera.h"

TCamera::TCamera(OBDEnums::CameraProjection projectionMode, f32 n, f32 f, f32 t, f32 b, f32 l, f32 r, f32 fo) : TEntity(){
	near = n;
	far = f;
	top = t;
	bottom = b;
	left = l;
	right = r;
	fov = fo;

	projection = projectionMode;

    recalculateProjectionMatrix();

    recalculateViewMatrix();
}

TCamera::~TCamera(){

}

void TCamera::beginDraw(){
    cache.setProjectionMatrix(pMat);
    cache.setViewMatrix(vMat);
	cache.setCameraPosition(cameraPosition);
}

void TCamera::endDraw(){

}

void TCamera::recalculateViewMatrix() {
    vMat = glm::lookAt(
        cameraPosition,  
        targetPosition, 
        glm::vec3(0,1,0) 
    );
}

void TCamera::recalculateProjectionMatrix(){
    if (projection == OBDEnums::CameraProjection::ProjectionPerspective){
        // Calculate aspect ratio
        f32 width = right - left;
        f32 height = bottom - top;
        //ToDo: revisar parametro FOV
        pMat = glm::perspective(glm::radians(fov), width / height, near, far);
    } else {
        pMat = glm::ortho(left, right, bottom, top, near, far);
    }
}

void TCamera::setTargetPosition(glm::vec3 p) {
    targetPosition = p;
    recalculateViewMatrix();
}

void TCamera::setCameraPosition(glm::vec3 p) {
    cameraPosition = p;
    recalculateViewMatrix();
}

void TCamera::setProjection(OBDEnums::CameraProjection cp){
    projection = cp;
	recalculateProjectionMatrix();
}

void TCamera::setFov(f32 f) {
    fov = f;
	recalculateProjectionMatrix();
}

void TCamera::setNear(f32 n){
    near = n;
	recalculateProjectionMatrix();
}

void TCamera::setFar(f32 f){
    far = f;
	recalculateProjectionMatrix();
}

void TCamera::setTop(f32 t){
    top = t;
	recalculateProjectionMatrix();
}

void TCamera::setBottom(f32 b){
    bottom = b;
	recalculateProjectionMatrix();
}

void TCamera::setLeft(f32 l){
    left = l;
	recalculateProjectionMatrix();
}

void TCamera::setRight(f32 r){
    right = r;
	recalculateProjectionMatrix();
}

glm::vec3 TCamera::getTargetPosition() {
    return targetPosition;
}

glm::vec3 TCamera::getCameraPosition() {
    return cameraPosition;
}

f32 TCamera::getFov() {
    return fov;
}

f32 TCamera::getNear(){
    return near;
}

f32 TCamera::getFar(){
    return far;
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

OBDEnums::CameraProjection TCamera::getProjection(){
    return projection;
}