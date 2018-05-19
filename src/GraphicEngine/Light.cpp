#include "Light.h"
#include "Window.h"

Light::Light(Vector3<f32> pos, Color c, f32 intensity) {
    l = Window::Instance()->getEngine()->createLight(OBDColor(c.r, c.g, c.b), intensity, 0.00001, 0.1);
	l->setPosition(glm::vec3(pos.x, pos.y, pos.z));
}

Light::~Light(){
    delete l;
	l = nullptr;
}

void Light::setPosition(Vector3<f32> pos){
	l->setPosition(glm::vec3(pos.x, pos.y, pos.z));
}

void Light::setType(i32 t) {
	l -> setType(t);
}