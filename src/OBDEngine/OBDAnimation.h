#ifndef OBDANIMATION_H
#define OBDANIMATION_H

#include "OBDEntity.h"
#include "OBDMesh.h"
#include "OBDMaterial.h"
#include "OBDSceneNode.h"

#include "Graphics/TTransform.h"

#include "ResourceManager/ResourceOBJ.h"

class OBDAnimation : public OBDEntity {
    public:
        /**
         * @brief Construct a new OBDAnimation object
         * 
         * @param parent parent node
         * @param objects vector containing all meshes that compose this animation
         * @param material material for all these meshes.
         */
        OBDAnimation(OBDSceneNode* parent, std::vector<ResourceOBJ*> *objects, ResourceMTL *material);

        /**
         * @brief Destroy the OBDAnimation object
         * 
         */
        ~OBDAnimation();

		/**
		 * @brief loop throught this animation's frames.
		 * 
		 */
		void updateFrame();

		/**
		 * @brief Set wether or not this entity is active.
		 * 
		 */
		void setActive(bool);

		/**
		 * @brief Set the current frame index. To be used when jumping to a specific frame.
		 * 
		 * @param nFrame frame index.
		 */
		void setCurrentFrame(i32 nFrame);

		/**
		 * @brief Get the Number Of Frames object
		 * 
		 * @return i32 total amount of frames
		 */
		i32 getNumberOfFrames();

		/**
		 * @brief Get the Material object
		 * 
		 * @return OBDMaterial* current material.
		 */
		OBDMaterial *getMaterial();
    private:
		std::vector<ResourceOBJ*> *objects;
		// Material
		ResourceMTL *objectMaterial;
		OBDMaterial *material;
		// All frames
		std::vector<OBDMesh*> *frames;
		// Frame management
		i32 numberOfFrames;
		i32 currentFrame;
		i32 nextFrame;
};

#endif