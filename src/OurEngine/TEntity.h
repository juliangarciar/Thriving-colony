#ifndef TENTITY_H
#define TENTITY_H

#include "TEnums.h"
#include <Types.h>
#include <glm/mat4x4.hpp>

class TEntity {
    public:
        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;

        static std::stack<glm::mat4> matrixStack;
    private:
};

#endif