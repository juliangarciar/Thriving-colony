#ifndef RESOURCEMATERIAL_H
#define RESOURCEMATERIAL_H

#include "Resource.h"

class ResourceMaterial : public Resource {
    public:
        ResourceMaterial();
        ~ResourceMaterial();

        void load(const char *path);

        void setIdentifier(const char *);
        const char *getIdentifier();
    private:
        void *buffer;
};

#endif