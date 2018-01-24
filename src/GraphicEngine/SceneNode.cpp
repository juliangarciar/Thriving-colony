#include "SceneNode.h"
#include "Window.h"

using namespace irr;

SceneNode::SceneNode() {
	scene::ISceneManager *w = Window::Instance() -> getSceneManager();
	node = w -> addEmptySceneNode(w -> getRootSceneNode());
	collisionManager = w -> getSceneCollisionManager();

	collisionNode = NULL;
}

SceneNode::SceneNode(SceneNode *parent) {
	scene::ISceneManager *w = Window::Instance() -> getSceneManager();
	node = w -> addEmptySceneNode(parent -> getSceneNode()); 
	collisionManager = w -> getSceneCollisionManager();

	collisionNode = NULL;
}

SceneNode::SceneNode(scene::ISceneNode *node){ 
	this -> node = node;
}

SceneNode::~SceneNode() {
	//ToDo: borrar node y collisionNode
	//node = NULL;
	//collisionNode = NULL;
}
 
SceneNode *SceneNode::getNodeCollision(Mouse *cursor){
	Vector2<int> p = cursor->getPosition();
	core::position2d<s32> pos = core::position2d<s32>(p.x, p.y);
	core::vector3df point;
	core::triangle3df triangle;
    const core::line3d<f32> ray = collisionManager -> getRayFromScreenCoordinates(pos);

	if (!collisionNode) {
		delete collisionNode;
		collisionNode = NULL;
	}

	scene::ISceneNode *n = collisionManager -> getSceneNodeAndCollisionPointFromRay(ray, point, triangle, 0, node);

	if (n) {
		collisionNode = new SceneNode(n);
		return collisionNode;
	}

	return NULL;
}

scene::ISceneNode *SceneNode::getSceneNode(){
	return node;
}