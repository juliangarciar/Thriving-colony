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

	//std::cout << std::endl;

	std::vector<u32> res = node->getCollisionID(l);
	if (res.size() > 0) {
		//std::cout << "-------" << res.size() << " DE LAS COSAS DE ARRIBA COLISIONAN CON EL RAYO--------" << std::endl;
		//std::cout << "RayStart " << l.start[0] << " " << l.start[1] << " " << l.start[2] << std::endl;
		//std::cout << "RayEnd " << l.end[0] << " " << l.end[1] << " " << l.end[2] << std::endl;
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