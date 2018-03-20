#include "Camera.h"
#include "Window.h"

using namespace irr;

Camera::Camera() {
    camera = Window::Instance() -> getSceneManager() -> addCameraSceneNode(0);
    // ToDo: Integracion
    //camera = Window::Instance() -> getSceneManager() -> createCamera();
}

Camera::~Camera() {
    //ToDo: borrar camara
    //camera = nullptr;
}

//Posicion de la camara
void Camera::setCameraPosition(Vector3<f32> position){
    // ToDo: Integracion
    // camera -> setCameraPosition(glm::vec3(p.x, p.y, p.z));
    camera -> setPosition(position.getVectorF());
}

//Hacia donde apunta la camara
void Camera::setTargetPosition(Vector3<f32> position){
    // ToDo: Integracion
    // camera -> setTargetPosition(glm::vec3(p.x, p.y, p.z));
    camera -> setTarget(position.getVectorF()); 
}

//Distancia del objetivo
void Camera::setShadowDistance(f32 zoom){
    // ToDo: Integracion
    // es igual
	camera -> setFarValue(zoom);
}

Vector3<f32> Camera::getCameraPosition(){
    // ToDo: Integracion
    // return Vector3<f32>(camera -> getCameraPosition());
    return Vector3<f32>(camera -> getPosition());
}

Vector3<f32> Camera::getTargetPosition(){
    // ToDo: Integracion
    // return Vector3<f32>(camera -> getTargetPosition());
    return Vector3<f32>(camera -> getTarget());;
}