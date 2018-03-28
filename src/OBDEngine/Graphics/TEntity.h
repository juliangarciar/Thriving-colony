#ifndef TENTITY_H
#define TENTITY_H

#include "../OBDTypes.h"
#include "../OBDEnums.h"
#include "TCache.h"

class TEntity {
    public:
        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;

        static TCache cache;
};

#endif