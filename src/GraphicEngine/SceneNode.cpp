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

SceneNode::SceneNode(OBDSceneNode *n) { 
	node = n;
}

SceneNode::~SceneNode() {
	delete node;
	node = nullptr;
}

void SceneNode::setPosition(Vector3<f32> pos) {
	if (pos.z > 0) pos.z *= -1;
    node->setPosition(glm::vec3(pos.x, pos.y, pos.z));
	node->refreshModelMatrix(glm::mat4(1.0f));
}

void SceneNode::setRotation(Vector3<f32> r) {
	node->setRotation(glm::vec3(r.x, r.y, r.z));
}

void SceneNode::setScale(Vector3<f32> s) {
    node->setScale(glm::vec3(s.x, s.y, s.z));
	node->refreshModelMatrix(glm::mat4(1.0f));
}

void SceneNode::setActive(bool a) {
    node->setActive(a);
}

i32 SceneNode::getNodeCollision(Vector2<i32> cursor) {
	OBDLine l = Window::Instance()->getEngine()->getRaycastFromScreenCoordinates(glm::vec2(cursor.x, cursor.y));

	std::vector<u32> res = node->getCollisionID(l);
	if (res.size() > 0) {
		return res[0];
	}
	return -1;
}

OBDSceneNode *SceneNode::getSceneNode() {
	return node;
}