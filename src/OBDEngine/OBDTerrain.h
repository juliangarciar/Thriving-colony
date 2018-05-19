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
		 * @brief 
		 * 
		 * @param  
		 * @param 
		 */
		OBDTerrain(OBDSceneNode*, std::string, f32 y_offset, f32 y_scale, i32 step);

		/**
		 * @brief 
		 * 
		 */
		virtual ~OBDTerrain();

        /**
         * @brief Set the glslTexture object
         * 
         */
        void setTexture(OBDTexture*);

		/**
		 * @brief Get the Ray Collision object
		 * 
		 * @param line
		 * @return glm::vec3 
		 */
		glm::vec3 getRayCollision(OBDLine);

		/**
		 * @brief 
		 * 
		 * @param x 
		 * @param z 
		 * @return f32 
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
		
        glslMesh *mesh;
        OBDMaterial *material;

		TNode* terrainNode;
};

#endif