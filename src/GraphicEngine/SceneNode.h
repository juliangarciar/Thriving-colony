#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <irrlicht.h>
#include <Types.h>
#include <MathEngine/Vector3.h>
#include <IOEngine/Mouse.h>

using namespace irr;

class SceneNode {
	public:
		SceneNode();
		SceneNode(SceneNode *parent);
		SceneNode(scene::ISceneNode *node);

		virtual ~SceneNode();

		//void addChild(scene::ISceneNode);
		SceneNode *getNodeCollision(Mouse *cursor);
		
		scene::ISceneNode *getSceneNode();
	private:
		scene::ISceneNode *node;
		scene::ISceneCollisionManager *collisionManager;

		SceneNode *collisionNode;
};

#endif