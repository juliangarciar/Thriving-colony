#include "TCamera.h"

TCamera::TCamera(TEnums::CameraProjection, f32, f32, f32, f32, f32, f32) : TEntity(){

}

TCamera::~TCamera(){

}

void TCamera::beginDraw(){

}

void TCamera::endDraw(){

}

void TCamera::setPerspective(f32 n, f32 f, f32 t, f32 b, f32 l, f32 r){
    setNear(n);
    projection = TEnums::CameraProjection::ProjectionPerspective;
    //ToDo: glm
}

void TCamera::setParallel(f32, f32, f32, f32, f32, f32){

}

void TCamera::setProjection(TEnums::CameraProjection cp){
    projection = cp;
}

void TCamera::setNear(f32 n){
    near = n;
}

void TCamera::setFar(f32 f){
    far = f;
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