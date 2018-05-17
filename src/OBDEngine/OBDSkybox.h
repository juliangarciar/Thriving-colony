#ifndef OBDSKYBOX_H
#define OBDSKYBOX_H

#include "OBDSceneNode.h"
#include "Graphics/TTexture.h"

#include "Graphics/TSkybox.h"

class OBDSkybox : public OBDEntity {
    
    public:
        /**
         * @brief 
         * 
         */
        OBDSkybox(TTexture* texture);

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
        void setTexture(TTexture* texture);

        /**
         * @brief Get the Skybox Entity object
         * 
         * @return TSkybox* 
         */
        TSkybox* getSkyboxEntity();

        /**
         * @brief Get the First Node object
         * 
         * @return TNode* 
         */
        TNode* getFirstNode();

    private:
        TNode* skyboxNode;
};

#endif
