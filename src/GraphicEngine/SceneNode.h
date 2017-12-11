#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <irrlicht.h>
#include <IOEngine/Mouse.h>
#include "Vector3.h"

using namespace irr;

class SceneNode {
	public:
		SceneNode();
		SceneNode(SceneNode *parent);
		SceneNode(scene::ISceneNode *node);

		virtual ~SceneNode();

		void addChild(scene::ISceneNode);
		SceneNode getNodeCollision(Mouse *cursor);
		
		scene::ISceneNode *getSceneNode();
	private:
		scene::ISceneNode *node;
		scene::ISceneCollisionManager *collisionManager;
};

#endif