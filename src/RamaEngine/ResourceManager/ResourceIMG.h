#ifndef RESOURCEIMG_H
#define RESOURCEIMG_H

#include <stdio.h>
#include "Resource.h"
#include "../Graphics/TResourceMesh.h"

class ResourceIMG : public Resource {
    public:
        ResourceIMG();
        ~ResourceIMG();

        void load(const char *path);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        void *getResource();
    private:
        void *resource;
};

#endif