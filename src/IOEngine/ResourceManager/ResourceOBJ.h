#ifndef RESOURCEOBJ_H
#define RESOURCEOBJ_H

#include "Resource.h"

class ResourceOBJ : public Resource {
    public:
        ResourceOBJ();
        ~ResourceOBJ();

        void load(const char *path);

        void setIdentifier(const char *);
        const char *getIdentifier();
    private:
        void *buffer;
};

#endif