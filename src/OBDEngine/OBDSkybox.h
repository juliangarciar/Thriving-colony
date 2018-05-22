#ifndef OBDSKYBOX_H
#define OBDSKYBOX_H

#include "OBDSceneNode.h"
#include "OBDShaderProgram.h"

#include "Graphics/TCubemapTexture.h"
#include "Graphics/TSkybox.h"

class OBDSkybox {
    
    public:
        /**
         * @brief 
         * 
         */
        OBDSkybox(OBDSceneNode *, OBDShaderProgram *, std::vector<ResourceIMG *>);

        /**
         * @brief 
         * 
         */
        ~OBDSkybox();

        /**
         * @brief Set the Texture object
         * 
         * @param texture 
         */
        void setTexture(std::vector<ResourceIMG *>);

    private:
        TNode* skyboxNode;
		TCubemapTexture *texture;
};

#endif
