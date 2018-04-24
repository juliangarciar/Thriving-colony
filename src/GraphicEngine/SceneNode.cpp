#include "SceneNode.h"
#include "Window.h"

using namespace irr;

SceneNode::SceneNode() {
	scene::ISceneManager *w = Window::Instance() -> getSceneManager();
	node = w -> addEmptySceneNode(w -> getRootSceneNode());
	collisionManager = w -> getSceneCollisionManager();

	collisionNode = nullptr;
}

SceneNode::SceneNode(SceneNode *parent) {
	scene::ISceneManager *w = Window::Instance() -> getSceneManager();
	node = w -> addEmptySceneNode(parent -> getSceneNode()); 
	collisionManager = w -> getSceneCollisionManager();

	collisionNode = nullptr;
}

SceneNode::SceneNode(scene::ISceneNode *n){ 
	node = n;
}

SceneNode::~SceneNode() {
	delete node;
	if (collisionNode != nullptr) delete collisionNode;
	node = nullptr;
	collisionNode = nullptr;
}
 
SceneNode *SceneNode::getNodeCollision(Mouse *cursor){
	Vector2<i32> p = cursor -> getPosition();
	core::position2d<s32> pos = core::position2d<s32>(p.x, p.y);
	core::vector3df point;
	core::triangle3df triangle;
    const core::line3d<f32> ray = collisionManager -> getRayFromScreenCoordinates(pos);

	if (!collisionNode) {
		delete collisionNode;
		collisionNode = nullptr;
	}

	scene::ISceneNode *n = collisionManager -> getSceneNodeAndCollisionPointFromRay(ray, point, triangle, 0, node);

	if (n && n != nullptr) {
		collisionNode = new SceneNode(n);
		return collisionNode;
	}

	return nullptr;
}

i32 SceneNode::getID(){
	return node->getID();
}

std::string SceneNode::getName(){
	return node->getName();
}

scene::ISceneNode *SceneNode::getSceneNode(){
	return node;
}