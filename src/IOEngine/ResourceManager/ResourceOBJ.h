#ifndef RESOURCEOBJ_H
#define RESOURCEOBJ_H

#include "Resource.h"
#include <OurEngine/TResourceMesh.h>

class ResourceOBJ : public Resource {
    public:
        ResourceOBJ();
        ~ResourceOBJ();

        void load(const char *path);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        std::vector<TResourceMesh*> *getResource();
    private:
        std::vector<TResourceMesh*> objMesh;
};

#endif