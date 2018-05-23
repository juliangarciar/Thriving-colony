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
         * @brief Construct a new OBDMesh object
         * 
         * @param mesh
         * @param material
         */
        OBDMesh(glslMesh*, OBDMaterial*);

        /**
         * @brief Destroy the OBDMesh object
         * 
         */
        ~OBDMesh();

		/**
		 * @brief update this object's bounding box
		 * 
		 */
		void refreshBoundingBox();

		/**
		 * @brief sets the bounding box
         * 
         * @param min point
         * @param max point
		 * 
		 */
		void setBoundingBox(glm::vec3, glm::vec3);

        /**
         * @brief Set the OBDMaterial object
         * 
         * @param new material
         */
        void setMaterial(OBDMaterial*);

        /**
         * @brief Set the material name
         * 
         */
        void setMaterialName(std::string);

        /**
         * @brief returns the material
         * 
         * @return std::string 
         */
        OBDMaterial *getMaterial();

        /**
         * @brief returns the name of the material
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