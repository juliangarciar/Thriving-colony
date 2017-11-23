#include "Camera.h"

using namespace irr;

Camera::Camera(scene::ISceneManager* sceneManager) {
    camera = sceneManager->addCameraSceneNode(0);
}

Camera::~Camera() {
    delete camera;
    camera = NULL;
}

//Posicion de la camara
void Camera::setPosition(Vector3<float> position){
    camera->setPosition(position.getVectorF());
}

//Hacia donde apunta la camara
void Camera::setTargetPosition(Vector3<float> position){
    camera->setTarget(position.getVectorF());
}

void Camera::setShadowDistance(float zoom){
	camera->setFarValue(zoom);
}