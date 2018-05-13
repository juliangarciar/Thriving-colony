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
 
i32 SceneNode::getNodeCollision(Vector2<i32> cursor){
	OBDLine l = Window::Instance()->getEngine()->getRaycastFromScreenCoordinates(glm::vec2(cursor.x, cursor.y));

	std::vector<u32> res = node->getCollisionID(l);
	if (res.size() > 0) {
		return res[0];
	}
	return -1;
}

OBDSceneNode *SceneNode::getSceneNode(){
	return node;
}