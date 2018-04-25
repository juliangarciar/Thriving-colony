#include "Camera.h"
#include "Window.h"

Camera::Camera() {
    c = Window::Instance()->getEngine()->createCamera();
}

Camera::~Camera() {
    delete c;
	c = nullptr;
}

//Posicion de la camara
void Camera::setCameraPosition(Vector3<f32> position){
    c->setCameraPosition(glm::vec3(position.x, position.y, position.z));
}

//Hacia donde apunta la camara
void Camera::setTargetPosition(Vector3<f32> position){
    c->setTargetPosition(glm::vec3(position.x, position.y, position.z));
}

//Distancia del objetivo
void Camera::setShadowDistance(f32 zoom){
	c->setFarValue(zoom);
}

Vector3<f32> Camera::getCameraPosition(){
    return Vector3<f32>(c->getCameraPosition().x, c->getCameraPosition().y, c->getCameraPosition().z);
}

Vector3<f32> Camera::getTargetPosition(){
    return Vector3<f32>(c->getTargetPosition().x, c->getTargetPosition().y, c->getTargetPosition().z);
}