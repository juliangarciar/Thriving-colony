#ifndef RESOURCEIMG_H
#define RESOURCEIMG_H

#include "Resource.h"
#include "ResourceManager.h"

#include <stb_image/stb_image.h>

class ResourceIMG : public Resource {
    public:
        ResourceIMG();
        ~ResourceIMG();

        void load(const char *path);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        unsigned char *getResource();
        int getWidth();
        int getHeight();
        int getChannels();
    private:
        unsigned char *resource;
        int width, height, channels;
        
};

#endif