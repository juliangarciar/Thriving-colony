#ifndef OBDSOURCEIMG_H
#define OBDSOURCEIMG_H

#include "Resource.h"
#include "ResourceManager.h"

class ResourceIMG : public Resource {
    public:
        ResourceIMG();
        ~ResourceIMG();

        void load(const char *path);
        void release();

		void setGLTexture();

        void setIdentifier(const char *);
        const char *getIdentifier();

        unsigned char *getResource();
        i32 getWidth();
        i32 getHeight();
        i32 getChannels();

        GLuint getTextureID();
    private:
        unsigned char *resource;
        i32 width, height, channels;

		bool glTextureSet;
        GLuint textureID;        
};

#endif