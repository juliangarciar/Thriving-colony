#include "Light.h"
#include "Window.h"

using namespace irr;

Light::Light(Vector3<f32> pos, Color c, f32 intensity) {
    light = Window::Instance()->getSceneManager()->addLightSceneNode(
		0, 
		core::vector3df(pos.x, pos.y, pos.z),
    	video::SColorf(c.a, c.r, c.g, c.b), intensity
	);
}

Light::~Light(){
    light->remove();
    light = nullptr;
}