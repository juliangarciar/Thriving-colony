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
		OBDTerrain(OBDSceneNode*, std::string);

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
		void generateTerrain(const char *path, float y_offset, float y_scale, int step);

		ResourceMesh mesh;
		ResourceMaterial material;

		TerTerrain *terrain;
		SDF *octree;
		std::vector<glm::vec3> vertex_vector;

		TNode* terrainNode;
};

#endif