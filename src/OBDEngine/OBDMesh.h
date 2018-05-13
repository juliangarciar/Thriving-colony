#ifndef OBDMESH_H
#define OBDMESH_H

#include <aabbtree/AABB.h>

#include "OBDEntity.h"
#include "OBDSceneNode.h"
#include "OBDTexture.h"

#include "ResourceManager/ResourceOBJ.h"
#include "ResourceManager/ResourceMTL.h"

#include "Graphics/TMesh.h"
#include "Graphics/TTransform.h"

class OBDMesh : public OBDEntity {
    public:
        /**
         * @brief 
         * 
         * @param  
         * @param 
         * @param 
         */
        OBDMesh(u32, ResourceMesh, ResourceMaterial);

        /**
         * @brief 
         * 
         * @param  
         * @param 
         * @param 
         */
        OBDMesh(OBDSceneNode*, u32, ResourceMesh, ResourceMaterial);

        /**
         * @brief 
         * 
         */
        ~OBDMesh();

        /**
         * @brief 
         * @param
         * @param sync
         */
        void loadTextures(ResourceManager*, bool);

		/**
		 * @brief 
		 * 
		 */
		void refreshBoundingBox();

        /**
         * @brief Set the Name 
         * 
         * @param a 
         */
        void setName(std::string a);

        /**
         * @brief Set the ResourceMaterial object
         * 
         */
        void setMaterial(ResourceMaterial);

        /**
         * @brief Set the glslTexture object
         * 
         */
        void setTexture(OBDTexture*);

        /**
         * @brief Set the Name object
         * 
         * @param n 
         */
        void setMaterialName(std::string n);

        /**
         * @brief Get the Name 
         * 
         * @return true 
         * @return false 
         */
        std::string getName();

        /**
         * @brief 
         * 
         * @return u32 
         */
        u32 getID();

        /**
         * @brief Get the Name object
         * 
         * @return std::string 
         */
        std::string getMaterialName();
        
        /**
         * @brief 
         * 
         * @return TMesh* 
         */
        TMesh* getMeshEntity();

		/**
		 * @brief Get the Bounding Box object
		 * 
		 * @return TNode* 
		 */
		aabb::AABB getBoundingBox();
    private:
		aabb::AABB boundingBox;

        TNode* meshNode;

        u32 ID;
		std::string name;
        std::string materialName;

        ResourceMesh mesh;
        ResourceMaterial material;
};

#endif