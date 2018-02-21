#include "Camera.h"
#include "Window.h"

using namespace irr;

Camera::Camera() {
    camera = Window::Instance() -> getSceneManager() -> addCameraSceneNode(0);
}

Camera::~Camera() {
    //ToDo: borrar camara
    //camera = nullptr;
}

//Posicion de la camara
void Camera::setCameraPosition(Vector3<f32> position){
    camera -> setPosition(position.getVectorF());
}

//Hacia donde apunta la camara
void Camera::setTargetPosition(Vector3<f32> position){
    camera -> setTarget(position.getVectorF()); 
}

//Distancia del objetivo
void Camera::setShadowDistance(f32 zoom){
	camera -> setFarValue(zoom);
}

Vector3<f32> Camera::getCameraPosition(){
    return Vector3<f32>(camera -> getPosition());
}

Vector3<f32> Camera::getTargetPosition(){
    return Vector3<f32>(camera -> getTarget());;
}