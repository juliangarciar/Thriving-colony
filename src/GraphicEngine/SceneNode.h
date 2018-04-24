#ifndef SCENE_NODE_H
#define SCENE_NODE_H

#include <irrlicht/irrlicht.h>
#include <Types.h>
#include <MathEngine/Vector3.h>
#include <IOEngine/Mouse.h>

using namespace irr;

class SceneNode {
	public:
		SceneNode();
		SceneNode(SceneNode *parent);

		virtual ~SceneNode();

		SceneNode *getNodeCollision(Mouse *cursor);

		i32 getID();
		std::string getName();
		
		scene::ISceneNode *getSceneNode();
	private:
		SceneNode(scene::ISceneNode *node);
		scene::ISceneNode *node;
		scene::ISceneCollisionManager *collisionManager;

		SceneNode *collisionNode;
};

#endif