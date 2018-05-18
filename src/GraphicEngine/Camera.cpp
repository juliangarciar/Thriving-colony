#include "Camera.h"
#include "Window.h"

using namespace irr;

Camera::Camera() {
    camera = Window::Instance() -> getSceneManager() -> addCameraSceneNode(0);
}

Camera::~Camera() {
    camera -> remove();
    delete camera;
    camera = nullptr;
}

//Posicion de la camara
void Camera::setCameraPosition(Vector3<f32> position){
    camera -> setPosition(core::vector3df(position.x, position.y, position.z));
}

//Hacia donde apunta la camara
void Camera::setTargetPosition(Vector3<f32> position){
    camera -> setTarget(core::vector3df(position.x, position.y, position.z)); 
}

//Distancia del objetivo
void Camera::setFarValue(f32 zoom){
	camera -> setFarValue(zoom);
}

Vector3<f32> Camera::getCameraPosition(){
    return Vector3<f32>(camera -> getPosition().X, camera -> getPosition().Y, camera -> getPosition().Z);
}

Vector3<f32> Camera::getTargetPosition(){
    return Vector3<f32>(camera -> getTarget().X, camera -> getTarget().Y, camera -> getTarget().Z);
}