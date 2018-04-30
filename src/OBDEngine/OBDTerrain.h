#ifndef OBDTERRAIN_H
#define OBDTERRAIN_H

#include <ter-terrain/ter-terrain.h>

#include "OBDEntity.h"
#include "OBDSceneNode.h"

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
		 */
		OBDTerrain(std::string);

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
		 * @brief 
		 * 
		 * @param tX 
		 * @param tY 
		 * @param tZ 
		 */
		void rotate(f32 rX, f32 rY, f32 rZ, f32 angle);

		/**
		 * @brief 
		 * 
		 */
		void scale(f32 sX, f32 sY, f32 sZ);

		/**
		 * @brief 
		 * 
		 */
		void translate(f32 tX, f32 tY, f32 tZ);

		/**
		 * @brief Set the Position
		 * 
		 * @param p 
		 */
		void setPosition(glm::vec3 p);

		/**
		 * @brief Set the Rotation
		 * 
		 * @param r 
		 * @param angle 
		 */
		void setRotation(glm::vec3 r, f32 angle);

		/**
		 * @brief Set the Scale
		 * 
		 * @param s 
		 */
		void setScale(glm::vec3 s);

		/**
		 * @brief Set the Active object
		 * 
		 * @param a 
		 */
		void setActive(bool a);

		/**
		 * @brief Get the Active object
		 * 
		 * @return true 
		 * @return false 
		 */
		bool getActive();

		/**
		 * @brief Get the First Node object
		 * 
		 * @return TNode* 
		 */
		TNode *getFirstNode();

		/**
		 * @brief 
		 * 
		 * @param x 
		 * @param z 
		 * @return f32 
		 */
		f32 getY(f32 x, f32 z);
	private:
		void generateTerrain();

		ResourceMesh mesh;
		ResourceMaterial material;

		TerTerrain *terrain;

		TNode* rotationNode;
		TNode* translationNode;
		TNode* scaleNode;
		TNode* terrainNode;

		glm::vec3 node_position;
		glm::vec3 node_rotation;
		glm::vec3 node_scale;
};

#endif