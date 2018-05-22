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

    for (auto& element : j["animations"]) {
		std::vector<std::string> animation_objects;
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

	frameTimer = new Timer(animationDelays->at(j["defaultAnimation"].get<std::string>()), true, false);
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

		frameTimer->changeDuration(animationDelays->at(animationName));
		frameTimer->restart();
	}
}

void Animation::preloadAnimation(std::string path){
	size_t last = path.rfind("/");
	std::string subpath = path.substr(0, last);

	ResourceJSON *animation = (ResourceJSON*)Window::Instance()->getEngineResourceManager()->getResource(path, true);
    json j = *animation -> getJSON();

    for (auto& element : j["animations"]) {
		std::string animationName = element["name"].get<std::string>();
    	for (auto& subelement : element["objects"]) {
			std::string objectName = subelement.get<std::string>();
			Window::Instance()->getEngineResourceManager()->loadResource(subpath+"/"+animationName+"/"+objectName, false);
		}
	}

	Window::Instance()->getEngineResourceManager()->loadResource(subpath+"/"+j["material"].get<std::string>(), false);
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

void Animation::setRandomFrame(){
  	i32 random = rand() % (currentAnimation->getNumberOfFrames() - 1) + 0;
	currentAnimation->setCurrentFrame(random);
}

Timer *Animation::getAnimationTimer(){
	return frameTimer;
}