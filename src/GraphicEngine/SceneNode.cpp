#include "SceneNode.h"
#include "Window.h"

using namespace irr;

SceneNode::SceneNode(){
	scene::ISceneManager *w = Window::Instance()->getSceneManager();
	node = w->addEmptySceneNode(w->getRootSceneNode());
	collisionManager = w->getSceneCollisionManager();
}

SceneNode::SceneNode(SceneNode *parent){
	scene::ISceneManager *w = Window::Instance()->getSceneManager();
	node = w->addEmptySceneNode(parent->getSceneNode()); 
}

SceneNode::SceneNode(scene::ISceneNode *node){
	this->node = node;
}

SceneNode::~SceneNode(){
	delete node;
	node = NULL;
}
 
SceneNode SceneNode::getNodeCollision(Mouse *cursor){
	scene::ISceneManager *w = Window::Instance()->getSceneManager();
	core::position2d<s32> pos = cursor->getCursor()->getPosition();
	core::vector3df point;
	core::triangle3df triangle;
	//scene::ISceneNode *node = 0;
    const core::line3d<f32> ray = collisionManager->getRayFromScreenCoordinates(pos);

	scene::ISceneNode *n = w->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(ray, point, triangle, 0, node);

	//ToDo: bien
	if (n) std::cout << n->getID() << std::endl;

	return SceneNode(n);
}

scene::ISceneNode *SceneNode::getSceneNode(){
	return node;
}