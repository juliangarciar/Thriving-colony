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
         * @brief 
         * 
         * @param parent 
         */
        OBDAnimation(OBDSceneNode* parent, std::vector<ResourceOBJ*> *objects, ResourceMTL *material);

        /**
         * @brief 
         * 
         */
        ~OBDAnimation();

		/**
		 * @brief 
		 * 
		 */
		void updateFrame();

		/**
		 * @brief Set the Active object
		 * 
		 */
		void setActive(bool);

		/**
		 * @brief Set the Frame object
		 * 
		 * @param nFrame 
		 */
		void setCurrentFrame(i32 nFrame);

		/**
		 * @brief Get the Number Of Frames object
		 * 
		 * @return i32 
		 */
		i32 getNumberOfFrames();

		/**
		 * @brief Get the Material object
		 * 
		 * @return OBDMaterial* 
		 */
		OBDMaterial *getMaterial();
    private:
		std::vector<ResourceOBJ*> *objects;
		ResourceMTL *objectMaterial;

		OBDMaterial *material;

		std::vector<OBDMesh*> *frames;
		i32 numberOfFrames;
		i32 currentFrame;
		i32 nextFrame;
};

#endif