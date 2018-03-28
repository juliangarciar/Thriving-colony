#ifndef OBDSOURCEOBJ_H
#define OBDSOURCEOBJ_H

#include "Resource.h"
#include "ResourceManager.h"

#include "Helpers/ResourceMesh.h"

class ResourceOBJ : public Resource {
    public:
        ResourceOBJ();
        ~ResourceOBJ();

        void load(const char *path);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        std::map<std::string, ResourceMesh*> *getResource();

        std::string getDefaultMaterialPath();
    private:
        std::map<std::string, ResourceMesh*> meshArray;
        std::string defaultMaterialPath;
};

#endif