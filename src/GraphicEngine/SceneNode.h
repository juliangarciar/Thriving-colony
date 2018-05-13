#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <OBDEngine/OBDSceneNode.h>

#include <Types.h>
#include <MathEngine/Vector3.h>
#include <IOEngine/Mouse.h>

class SceneNode {
	public:
		SceneNode();
		SceneNode(SceneNode *parent);

		virtual ~SceneNode();

		SceneNode *getNodeCollision(Mouse *cursor);

		i32 getID();
		std::string getName();
		
		OBDSceneNode *getSceneNode();
	private:
		SceneNode(OBDSceneNode *node);
		SceneNode *collisionNode;

		OBDSceneNode *node;
};

#endif