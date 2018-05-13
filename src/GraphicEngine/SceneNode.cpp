#include "SceneNode.h"
#include "Window.h"

SceneNode::SceneNode() {
	collisionNode = nullptr;
	node = Window::Instance()->getEngine()->createSceneNode();
}

SceneNode::SceneNode(SceneNode *parent) {
	collisionNode = nullptr;
	node = Window::Instance()->getEngine()->createSceneNode(parent->getSceneNode());
}

SceneNode::SceneNode(OBDSceneNode *n){ 
	node = n;
}

SceneNode::~SceneNode() {
	delete node;
	node = nullptr;
}
 
SceneNode *SceneNode::getNodeCollision(Mouse *cursor){
	OBDLine l = Window::Instance()->getEngine()->getRaycastFromScreenCoordinates(glm::vec2(cursor->getPosition().x, cursor->getPosition().y));

	std::vector<u32> res = node->getCollisionID(l);
	if (res.size() > 0) {
	}
	return nullptr;
}

i32 SceneNode::getID(){
	
}

std::string SceneNode::getName(){
	
}

OBDSceneNode *SceneNode::getSceneNode(){
	return node;
}