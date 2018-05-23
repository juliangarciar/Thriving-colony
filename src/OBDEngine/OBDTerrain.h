#ifndef OBDTERRAIN_H
#define OBDTERRAIN_H

#include <ter-terrain/ter-terrain.h>
#include <ter-terrain/octree.h>

#include "OBDEntity.h"
#include "OBDSceneNode.h"
#include "OBDTexture.h"

#include "ResourceManager/ResourceIMG.h"
#include "ResourceManager/ResourceOBJ.h"
#include "ResourceManager/ResourceMTL.h"

#include "Graphics/TTransform.h"
#include "Graphics/TMesh.h"

class OBDTerrain : public OBDEntity {
	public:
		/**
		 * @brief Construct a new OBDTerrain object
		 * 
		 * @param y_offset 
		 * @param y_scale 
		 * @param step 
		 */
		OBDTerrain(OBDSceneNode*, std::string, f32 y_offset, f32 y_scale, i32 step);

		/**
		 * @brief Destroy the OBDTerrain object
		 * 
		 */
		virtual ~OBDTerrain();
		
		/**
		 * @brief update the terrain's model matrix
		 * 
		 */
		void refreshModelMatrix(glm::mat4);

        /**
         * @brief Set the glslTexture object
         * 
         */
        void setTexture(OBDTexture*);

		/**
		 * @brief Get the Raycast Collision point
		 * 
		 * @param line
		 * @return glm::vec3 
		 */
		glm::vec3 getRayCollision(OBDLine);

		/**
		 * @brief get the y component of a given point of the terrain
		 * 
		 * @param x 
		 * @param z 
		 * @return f32 y component
		 */
		f32 getY(f32 x, f32 z);

		/**
		 * @brief Get the Terrain Mesh object
		 * 
		 * @return TMesh* 
		 */
		TMesh *getTerrainMesh();
	private:
		TerTerrain *terrain;
		SDF *octree;
		std::vector<glm::vec3> vertex_vector;

		// Buffers
		std::vector<f32> *vbo;
		std::vector<u32> *ibo;
		GLuint vboid;
		GLuint iboid;
		
        glslMesh *mesh;
        OBDMaterial *material;

		TNode* terrainNode;
};

#endif