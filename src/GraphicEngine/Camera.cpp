#include "Camera.h"
#include "Window.h"

using namespace irr;

Camera::Camera() {
    camera = Window::Instance()->getSceneManager()->addCameraSceneNode(0);
}

Camera::~Camera() {
    //ToDo: borrar camara
    //camera = NULL;
}

//Posicion de la camara
void Camera::setCameraPosition(Vector3<float> position){
    camera->setPosition(position.getVectorF());
}

//Hacia donde apunta la camara
void Camera::setTargetPosition(Vector3<float> position){
    camera->setTarget(position.getVectorF()); 
}

//Distancia del objetivo
void Camera::setShadowDistance(float zoom){
	camera->setFarValue(zoom);
}

Vector3<float> Camera::getCameraPosition(){
    return Vector3<float>(camera->getPosition());
}

Vector3<float> Camera::getTargetPosition(){
    return Vector3<float>(camera->getTarget());;
}