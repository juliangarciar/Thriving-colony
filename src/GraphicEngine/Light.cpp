#include "Light.h"
#include "Window.h"

using namespace irr;

Light::Light(Vector3<f32> pos, f32 intensity) {
    light = Window::Instance()->getSceneManager()->addLightSceneNode(0, core::vector3df(pos.x, pos.y, pos.z),
    	video::SColorf(1.0f,1.0f,1.0f,1.0f), intensity); //ToDo: aqui no deberian haber datos
}

Light::~Light(){
    light->remove();
    light = nullptr;
}