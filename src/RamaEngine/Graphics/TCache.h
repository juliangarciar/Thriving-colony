#ifndef TCACHE_H
#define TCACHE_H

#include "../RETypes.h"
#include "../REEnums.h"

class TCache {
    public:
        TCache();
        ~TCache();

        void setCurrentProgramID(GLuint);
        GLuint getCurrentProgramID();

        std::vector<GLuint> generateAllParamIDs(int);
        void setAllParamIDs(std::vector<GLuint>);

        void setParamID(REEnums::ShaderParams, GLuint);
        GLuint getParamID(REEnums::ShaderParams);

        void setModelMatrix(glm::mat4);
        glm::mat4 getModelMatrix();

        void setViewMatrix(glm::mat4);
        glm::mat4 getViewMatrix();

        void setProjectionMatrix(glm::mat4);
        glm::mat4 getProjectionMatrix();

        std::vector<Light> *getLights();

        std::stack<glm::mat4>& getMatrixStack();
    private:
        GLuint currentProgramID;

        std::stack<glm::mat4> matrixStack;

        std::vector<GLuint> parameterIDs;

        glm::mat4 modelMatrix;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        std::vector<Light> *lights;
};

#endif