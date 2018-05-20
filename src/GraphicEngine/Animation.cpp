#include "Animation.h"
#include "Window.h"

Animation::Animation(SceneNode* parent, std::string animationJSON) {
	animationLayer = new SceneNode(parent);

	animations = new std::map<std::string, OBDAnimation*>();
	animationDelays = new std::map<std::string, f32>();

	size_t last = animationJSON.rfind("/");
	std::string subpath = animationJSON.substr(0, last);

	ResourceJSON *animation = (ResourceJSON*)Window::Instance()->getEngine()->getResourceManager()->getResource(animationJSON, true);
    json j = *animation -> getJSON();

	std::vector<std::string> animation_objects;
    for (auto& element : j["animations"]) {
		std::string animationName = element["name"].get<std::string>();
    	for (auto& subelement : element["objects"]) {
			std::string objectName = subelement.get<std::string>();

			animation_objects.push_back(subpath+"/"+animationName+"/"+objectName);
		}
		OBDAnimation *tempAnimation = Window::Instance()->getEngine()->createAnimation(animationLayer->getSceneNode(), animation_objects, subpath+"/"+j["material"].get<std::string>(), true);
		tempAnimation->setActive(false);

		animations->insert(std::pair<std::string, OBDAnimation*>(animationName, tempAnimation));
		animationDelays->insert(std::pair<std::string, f32>(animationName, element["delay"].get<f32>()));
	}

	currentAnimation = animations->at(j["defaultAnimation"].get<std::string>());
	currentAnimation -> setActive(true);

	/* Por que un string */
	frameTimer = new Timer(animationDelays->at(j["defaultAnimation"].get<std::string>()), true);
	frameTimer -> setCallback([&]() {
		currentAnimation->updateFrame();
	});
}

Animation::~Animation() {
	animationLayer = nullptr;
	for (std::map<std::string, OBDAnimation*>::iterator it = animations->begin(); it != animations->end(); ++it) {
		delete it->second;
	}
	animations->clear();
	delete animations;
	animations = nullptr;
	delete frameTimer;
	frameTimer = nullptr;
	delete animationLayer;
}

//ToDo: cola de animaciones
void Animation::changeAnimation(std::string animationName) {
	auto it = animations->find(animationName);
	if (it != animations->end()) {
		currentAnimation -> setActive(false);
		
		currentAnimation = it->second;
		currentAnimation -> setActive(true);
		//currentAnimation -> setFrame(0);

		frameTimer->changeDuration(animationDelays->at(animationName));
		frameTimer->restart();
	}
}

void Animation::setPosition(Vector3<f32> pos) {
    animationLayer->setPosition(pos);
}

void Animation::setRotation(Vector3<f32> r) {
	animationLayer->setRotation(r);
}

void Animation::setScale(Vector3<f32> s) {
    animationLayer->setScale(s);
}

void Animation::setActive(bool a) {
    animationLayer->setActive(a);
}

void Animation::setColor(Color c) {
	currentAnimation->getMaterial()->setDiffuseColor(OBDColor(c.r, c.g, c.b, c.a));
}