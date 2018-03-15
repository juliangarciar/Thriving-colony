#ifndef TENTITY_H
#define TENTITY_H

#include "../RETypes.h"
#include "../REEnums.h"
#include "TMatrixCache.h"

static std::stack<glm::mat4> matrixStack;

class TEntity {
    public:
        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;
};

#endif