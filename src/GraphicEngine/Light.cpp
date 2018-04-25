#include "Light.h"
#include "Window.h"

//ToDo: color
Light::Light(Vector3<f32> pos, f32 intensity) {
    l = Window::Instance()->getEngine()->createLight(OBDColor(1, 1, 1), intensity);
}

Light::~Light(){
    
}