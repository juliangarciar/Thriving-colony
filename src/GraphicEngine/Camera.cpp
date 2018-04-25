#include "Camera.h"
#include "Window.h"

Camera::Camera() {
    c = Window::Instance()->getEngine()->createCamera();
}

Camera::~Camera() {
    
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
	
}

Vector3<f32> Camera::getCameraPosition(){
    
}

Vector3<f32> Camera::getTargetPosition(){
    
}