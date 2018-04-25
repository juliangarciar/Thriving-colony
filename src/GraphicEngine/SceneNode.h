#ifndef SCENE_NODE_H
#define SCENE_NODE_H

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
		
		//scene::ISceneNode *getSceneNode();
	private:
		//SceneNode(scene::ISceneNode *node);
		SceneNode *collisionNode;

		
};

#endif