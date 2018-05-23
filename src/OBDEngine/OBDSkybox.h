#ifndef OBDSKYBOX_H
#define OBDSKYBOX_H

#include "OBDSceneNode.h"
#include "OBDShaderProgram.h"

#include "Graphics/TCubemapTexture.h"
#include "Graphics/TSkybox.h"

class OBDSkybox {
    
    public:
        /**
         * @brief Construct a new OBDSkybox object
         * 
         * 
         * @param parent
         * @param shader used to render the skybox
         * @param vector of textures
         */
        OBDSkybox(OBDSceneNode *, OBDShaderProgram *, std::vector<ResourceIMG *>);

        /**
         * @brief Destroy the OBDSkybox object
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
