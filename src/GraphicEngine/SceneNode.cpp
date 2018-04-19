#include "SceneNode.h"
#include "Window.h"

using namespace irr;

SceneNode::SceneNode() {
	scene::ISceneManager *w = Window::Instance() -> getSceneManager();
	node = w -> addEmptySceneNode(w -> getRootSceneNode());
	collisionNode = nullptr;
}

SceneNode::SceneNode(SceneNode *parent) {
	scene::ISceneManager *w = Window::Instance() -> getSceneManager();
	node = w -> addEmptySceneNode(parent -> getSceneNode()); 
	collisionNode = nullptr;
}

SceneNode::SceneNode(scene::ISceneNode *n){ 
	node = n;
}

SceneNode::~SceneNode() {
	node -> remove();
	node = nullptr;
}
 
SceneNode *SceneNode::getNodeCollision(Mouse *cursor){
	scene::ISceneCollisionManager *collisionManager = Window::Instance() -> getSceneManager() -> getSceneCollisionManager();

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

	if (n) {
		collisionNode = new SceneNode(n);
		return collisionNode;
	}

	return nullptr;
}

scene::ISceneNode *SceneNode::getSceneNode(){
	return node;
}