#ifndef OBDOBJECT_H
#define OBDOBJECT_H

#include "OBDEntity.h"
#include "OBDMesh.h"
#include "OBDSceneNode.h"

#include "ResourceManager/ResourceOBJ.h"
#include "ResourceManager/ResourceMTL.h"

#include "Graphics/TTransform.h"
#include "Graphics/TMesh.h"

class OBDObject : public OBDEntity {
    public:
        /**
         * @brief Construct a new OBDMesh object
         * 
         * @param parent 
         * @param obj 
         * @param mtl 
         */
        OBDObject(OBDSceneNode* parent, u32, ResourceOBJ *obj, ResourceMTL *mtl);

        /**
         * @brief Destroy the OBDObject object
         * 
         */
        virtual ~OBDObject();

        /**
         * @brief 
         * @param r 
         * @param sync 
         */
        void loadTextures(ResourceManager*, bool);

        /**
         * @brief Set the Material object
         * 
         * @param mtl 
         */
        void setMaterial(ResourceMTL *mtl);

		/**
		 * @brief 
		 * 
		 */
		void refreshBoundingBox();

		/**
		 * @brief 
		 * 
		 */
		void refreshModelMatrix(glm::mat4);

        /**
         * @brief Get the Mesh object
         * 
         * @return TMesh* 
         */
        OBDMesh *getMesh(std::string);

        /**
         * @brief Get the Meshes object
         * 
         * @return std::map<std::string, OBDMesh*> 
         */
        std::map<std::string, OBDMesh*> getMeshes();

		/**
		 * @brief Get the Bounding Box object
		 * 
		 * @return aabb::AABB 
		 */
		aabb::AABB getBoundingBox();

        /**
         * @brief 
         * 
         * @return u32 
         */
        u32 getID();

        /**
         * @brief Get the Mesh Amount object
         * 
         * @return u32 
         */
        u32 getMeshAmount();
    private:
		aabb::AABB boundingBox;

        std::map<std::string, OBDMesh*> meshes;
		
        u32 ID;
};

#endif