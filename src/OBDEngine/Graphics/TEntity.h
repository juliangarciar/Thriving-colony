#ifndef TENTITY_H
#define TENTITY_H

#include "../OBDTypes.h"
#include "../OBDEnums.h"
#include "TCache.h"

class TEntity {
    public:
        //Implement after inheritance.
        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;
        // Reference the matrix cache
        static TCache cache;
};

#endif