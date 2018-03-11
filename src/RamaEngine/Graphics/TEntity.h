#ifndef TENTITY_H
#define TENTITY_H

#include "../RETypes.h"
#include "../REEnums.h"

static std::stack<glm::mat4> matrixStack;

static GLuint MVPID;
static GLuint projectionMatrixID;
static GLuint viewMatrixID;
static GLuint modelMatrixID;
static GLuint textureID;

static glm::mat4 modelMatrix;
static glm::mat4 viewMatrix;
static glm::mat4 projectionMatrix;

class TEntity {
    public:
        virtual void beginDraw() = 0;
        virtual void endDraw() = 0;
};

#endif