#ifndef TENTITY_H
#define TENTITY_H

#include "../OBDETypes.h"
#include "../OBDEEnums.h"
#include "TMatrixCache.h"

class TEntity {
    public:
        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;
};

#endif