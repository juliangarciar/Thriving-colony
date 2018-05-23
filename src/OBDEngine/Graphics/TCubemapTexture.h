#ifndef TCUBEMAPTEXTURE_H
#define TCUBEMAPTEXTURE_H

#include "../OBDTypes.h"

class ResourceIMG;

class TCubemapTexture {
    public:
        /**
         * @brief Construct a new TCubemapTexture object. A vector of 6 and only 6 images must be passed
         * as parameter, each for each face of the cube's.
         * 
         */
        TCubemapTexture(std::vector<ResourceIMG *>);

        /**
         * @brief Destroy the TCubemapTexture object. Memory is not actually cleared here, but on the resourceIMG.
         * 
         */
        ~TCubemapTexture();

        /**
         * @brief Get the id of the texture.
         * 
         * @return GLuint id of the texture
         */
        GLuint getTextureID();
    private:
        GLuint textureID;
};
    
#endif