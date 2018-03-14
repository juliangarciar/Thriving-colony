#ifndef RESOURCEOBJ_H
#define RESOURCEOBJ_H

#include "Resource.h"
#include "ResourceManager.h"

#include "../Graphics/TResourceMesh.h"

class ResourceOBJ : public Resource {
    public:
        ResourceOBJ(ResourceManager *);
        ~ResourceOBJ();

        void load(const char *path, bool sync);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        std::vector<TResourceMesh*> *getResource();
    private:
        std::vector<TResourceMesh*> objMesh;
        ResourceManager *loadedBy;
};

#endif