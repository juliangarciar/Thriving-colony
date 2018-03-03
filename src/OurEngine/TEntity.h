#ifndef TENTITY_H
#define TENTITY_H

#include "TEnums.h"
#include <Types.h>
#include <glm/mat4x4.hpp>
#include <stack>

static std::stack<glm::mat4> matrixStack;
// Model matrix/ Camera matrix/ Light matrix
static glm::mat4 modelMatrix = glm::mat4(1.0f);

class TEntity {
    public:
        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;

    private:
};

#endif