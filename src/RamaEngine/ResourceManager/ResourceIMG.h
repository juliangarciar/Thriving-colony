#ifndef RESOURCEIMG_H
#define RESOURCEIMG_H

#include "Resource.h"
#include "ResourceManager.h"

#include "../Graphics/TResourceMesh.h"
//#include <SOIL/SOIL.h>

class ResourceIMG : public Resource {
    public:
        ResourceIMG(ResourceManager *);
        ~ResourceIMG();

        void load(const char *path, bool sync);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        void *getResource();
        int getWidth();
        int getHeight();
        int getChannels();
    private:
        void *resource;
        int width, height, channels;
        ResourceManager *loadedBy;
};

#endif