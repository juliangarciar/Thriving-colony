#ifndef OBDMESH_H
#define OBDMESH_H

#include <aabbtree/AABB.h>

#include "OBDEntity.h"
#include "OBDMaterial.h"
#include "OBDTexture.h"

#include "Graphics/TMesh.h"

class OBDMesh : public OBDEntity {
    public:
        /**
         * @brief 
         * 
         * @param  
         * @param 
         * @param 
         */
        OBDMesh(glslMesh*, OBDMaterial*);

        /**
         * @brief 
         * 
         */
        ~OBDMesh();

		/**
		 * @brief 
		 * 
		 */
		void refreshBoundingBox();

		/**
		 * @brief 
		 * 
		 */
		void setBoundingBox(glm::vec3, glm::vec3);

        /**
         * @brief Set the OBDMaterial object
         * 
         */
        void setMaterial(OBDMaterial*);

        /**
         * @brief Set the material name
         * 
         */
        void setMaterialName(std::string);

        /**
         * @brief 
         * 
         * @return std::string 
         */
        OBDMaterial *getMaterial();

        /**
         * @brief 
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
        TNode* meshNode;

		std::string materialName;

		glm::vec4 aabbMin;
		glm::vec4 aabbMax;
		aabb::AABB boundingBox;
		
        glslMesh *mesh;
        OBDMaterial *material;
};

#endif