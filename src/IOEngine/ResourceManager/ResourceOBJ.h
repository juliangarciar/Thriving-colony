#ifndef RESOURCEOBJ_H
#define RESOURCEOBJ_H

#include "Resource.h"
#include <objloader/OBJ_Loader.h>
#include <OurEngine/TResourceMesh.h>

class ResourceOBJ : public Resource {
    public:
        ResourceOBJ();
        ~ResourceOBJ();

        void load(const char *path);

        void setIdentifier(const char *);
        const char *getIdentifier();

        std::vector<TResourceMesh*> *getOBJMesh();
    private:
        std::vector<TResourceMesh*> *objMesh;
};

#endif