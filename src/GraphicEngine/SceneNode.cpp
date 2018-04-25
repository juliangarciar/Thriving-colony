#include "SceneNode.h"
#include "Window.h"

SceneNode::SceneNode() {
	collisionNode = nullptr;

}

SceneNode::SceneNode(SceneNode *parent) {
	collisionNode = nullptr;

}

/*SceneNode::SceneNode(scene::ISceneNode *n){ 
	node = n;
}*/

SceneNode::~SceneNode() {
	
}
 
SceneNode *SceneNode::getNodeCollision(Mouse *cursor){
	
	return nullptr;
}

i32 SceneNode::getID(){
	
}

std::string SceneNode::getName(){
	
}

/*scene::ISceneNode *SceneNode::getSceneNode(){
	return node;
}*/