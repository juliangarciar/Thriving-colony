#ifndef TENTITY_H
#define TENTITY_H

#include "../RETypes.h"
#include "../REEnums.h"

static std::stack<glm::mat4> matrixStack;
// Model matrix/ Camera matrix/ Light matrix
//ToDo O AQUI O EN EL RAMAENGINE
static glm::mat4 modelMatrix = glm::mat4(1.0f);
static glm::mat4 viewMatrix = glm::mat4(1.0f);
static glm::mat4 projectionMatrix = glm::mat4(1.0f);

class TEntity {
    public:
        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;

    private:
};

#endif