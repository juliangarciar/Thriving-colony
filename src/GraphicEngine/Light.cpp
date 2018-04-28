#include "Light.h"
#include "Window.h"

//ToDo: color
Light::Light(Vector3<f32> pos, f32 intensity) {
    l = Window::Instance()->getEngine()->createLight(OBDColor(1, 1, 1), intensity);
	l->setPosition(glm::vec3(pos.x, pos.y, pos.z));
}

Light::~Light(){
    delete l;
	l = nullptr;
}

void Light::setPosition(Vector3<f32> pos){
	l->setPosition(glm::vec3(pos.x, pos.y, pos.z));
}