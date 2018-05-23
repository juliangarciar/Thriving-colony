#ifndef OBDSCENENODE_H
#define OBDSCENENODE_H

#include <aabbtree/AABB.h>

#include "OBDEntity.h"

#include "Graphics/TTransform.h"

class OBDSceneNode : public OBDEntity {
    public:
        /**
         * @brief create a new scene node
         * 
         * @param parent 
         */
        OBDSceneNode(TNode*);

        /**
         * @brief create a new scene node as a child of a given scene node
         * 
         * @param parent 
         */
        OBDSceneNode(OBDSceneNode*);

        /**
         * @brief Destroy the OBDSceneNode object
         * 
         */
        virtual ~OBDSceneNode();

        /**
         * @brief add a child to this scenenode children list
         * 
         */
        void addChild(OBDEntity *);

        /**
         * @brief add a child to this scenenode children list
         * 
         */
        void addChild(TNode *);

		/**
		 * @brief reset this node's model matrix
		 * 
		 */
		void refreshModelMatrix(glm::mat4);

		/**
		 * @brief add this scenenode bounding box to the octree
		 * 
         * @param id
         * @param bounding box
		 */
		void insertBoundingBox(u32, aabb::AABB);

		/**
		 * @brief refresh this scenenode's bounding box in the octree
		 * 
         * @param id
         * @param bounding box
		 */
		void refreshBoundingBox(u32, aabb::AABB);

		/**
		 * @briefremove this scenenode's bounding from the octree
		 * 
         * @param id
		 */
		void removeBoundingBox(u32);

		/**
		 * @brief Get the Collision I D object
		 * 
		 * @return u32 
		 */
		std::vector<u32> getCollisionID(OBDLine);

    private:
        std::vector<OBDEntity*> children;

		aabb::Tree octree;
};

#endif