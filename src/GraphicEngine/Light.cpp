#include "Light.h"
#include "Window.h"

using namespace irr;

Light::Light(Vector3<f32> pos, f32 intensity) {
    light = Window::Instance()->getSceneManager()->addLightSceneNode(0, pos.getVectorF(),
    video::SColorf(1.0f,1.0f,1.0f,1.0f), intensity);
}

Light::~Light(){
    light->remove();
}