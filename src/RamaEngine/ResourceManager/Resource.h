#ifndef RESOURCE_H
#define RESOURCE_H

#include "../RETypes.h"
#include "../REEnums.h"

class Resource {
    public:
        virtual void load(const char *path) = 0;
        virtual void release() = 0;

        virtual void setIdentifier(const char *) = 0;
        virtual const char *getIdentifier() = 0;
    protected:
        const char *identifier;
    private:
        
};

#endif