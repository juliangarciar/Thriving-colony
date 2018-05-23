#ifndef OBDSOURCEIMG_H
#define OBDSOURCEIMG_H

#include "Resource.h"
#include "ResourceManager.h"

class ResourceIMG : public Resource {
    public:
        /**
         * @brief Construct a new Resource I M G object
         * 
         */
        ResourceIMG();
        /**
         * @brief Destroy the Resource I M G object
         * 
         */
        ~ResourceIMG();
        /**
         * @brief load the obj file
         * 
         * @param path path to file
         */
        void load(const char *path);
        /**
         * @brief release this resource, freeing up the memory it occupied.
         * 
         */
        void release();
        /**
         * @brief creates a gltexture from the image
         * 
         */
		void setGLTexture();
        /**
         * @brief Set the ID
         * 
         */
        void setIdentifier(const char *);
        /**
         * @brief returns the id of the resource
         * 
         * @return const char* 
         */
        const char *getIdentifier();
        /**
         * @brief Get the actual image Resource 
         * 
         * @return unsigned char* 
         */
        unsigned char *getResource();
        /**
         * @brief Get the Width of the image
         * 
         * @return i32 width
         */
        i32 getWidth();
        /**
         * @brief Get the Height of the image
         * 
         * @return i32 height
         */
        i32 getHeight();
        /**
         * @brief Get the number of channels by the image
         * 
         * @return i32 number of channels
         */
        i32 getChannels();
        /**
         * @brief returns the id of the opengl textue previously generated
         * 
         * @return GLuint id of the texture
         */
        GLuint getTextureID();
    private:
        unsigned char *resource;
        // Data relative to the image
        i32 width, height, channels;

		bool glTextureSet;
        GLuint textureID;        
};

#endif