#ifndef OBDSHADERPROGRAM_H
#define OBDSHADERPROGRAM_H

#include <GL/glew.h>
#include "OBDTypes.h"
#include "OBDEnums.h"

#include "Graphics/TShader.h"

class OBDShaderProgram {
    public:
        /**
         * @brief 
         * @param shader
         * @param shader
         */
        OBDShaderProgram(ResourceGLSL*, ResourceGLSL*);

        /**
         * @brief 
         * 
         */
        ~OBDShaderProgram();

        /**
         * @brief Get the param ids object
         * 
         * @return GLuint 
         */
        std::vector<GLuint> getParamIDs();

        /**
         * @brief Get the Shader Program object
         * 
         * @return GLuint 
         */
        GLuint getShaderProgram();
    private:
        GLuint pid;
        TShader *vertexShader;
        TShader *fragmentShader;

        std::vector<GLuint> paramIDs;
};

#endif