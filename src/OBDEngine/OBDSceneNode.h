#ifndef OBDSCENENODE_H
#define OBDSCENENODE_H

#include <aabbtree/AABB.h>

#include "OBDEntity.h"

#include "Graphics/TTransform.h"

class OBDSceneNode : public OBDEntity {
    public:
        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDSceneNode(TNode*);

        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDSceneNode(OBDSceneNode*);

        /**
         * @brief 
         * 
         */
        virtual ~OBDSceneNode();

        /**
         * @brief 
         * 
         */
        void addChild(OBDEntity *);

        /**
         * @brief 
         * 
         */
        void addChild(TNode *);

		/**
		 * @brief 
		 * 
		 */
		void refreshModelMatrix(glm::mat4);

		/**
		 * @brief 
		 * 
         * @param s 
         * @param s 
		 */
		void insertBoundingBox(u32, aabb::AABB);

		/**
		 * @brief 
		 * 
         * @param s 
         * @param s 
		 */
		void refreshBoundingBox(u32, aabb::AABB);

		/**
		 * @brief 
		 * 
         * @param s 
         * @param s 
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