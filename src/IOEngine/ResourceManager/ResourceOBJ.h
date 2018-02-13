#ifndef RESOURCEOBJ_H
#define RESOURCEOBJ_H

#include "Resource.h"

class ResourceOBJ : public Resource {
    public:
        void load(const char *path);

        void setIdentifier(const char *);
        const char *getIdentifier();
    private:
        const char *identifier;
        void *buffer;
};

#endif