#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <OBDEngine/OBDSceneNode.h>

#include <Types.h>
#include <MathEngine/Vector2.h>
#include <MathEngine/Vector3.h>

class SceneNode {
	public:
		SceneNode();
		SceneNode(SceneNode *parent);

		virtual ~SceneNode();

		i32 getNodeCollision(Vector2<i32> cursor);
		
		OBDSceneNode *getSceneNode();
	private:
		SceneNode(OBDSceneNode *node);
		SceneNode *collisionNode;

		OBDSceneNode *node;
};

#endif