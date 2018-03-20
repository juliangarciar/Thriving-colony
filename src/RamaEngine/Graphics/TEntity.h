#ifndef TENTITY_H
#define TENTITY_H

#include "../RETypes.h"
#include "../REEnums.h"
#include "TMatrixCache.h"

class TEntity {
    public:
        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;
};

#endif