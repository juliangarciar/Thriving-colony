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