#ifndef OBDSOURCEMTL_H
#define OBDSOURCEMTL_H

#include "Resource.h"
#include "ResourceManager.h"

#include "Helpers/ResourceMaterial.h"

class ResourceMTL : public Resource {
    public:
        ResourceMTL();
        ~ResourceMTL();

        void load(const char *path);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        std::map<std::string, ResourceMaterial*> *getResource();
    private:
        std::map<std::string, ResourceMaterial*> materialArray;
        
};

#endif