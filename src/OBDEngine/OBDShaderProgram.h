#ifndef OBDSHADERPROGRAM_H
#define OBDSHADERPROGRAM_H

#include "OBDTypes.h"
#include "OBDEnums.h"

#include "Graphics/TShader.h"

class OBDShaderProgram {
    public:
        /**
         * @brief create a new shader program
         * @param shader vertex shader
         * @param shader fragment shader
         */
        OBDShaderProgram(ResourceGLSL*, ResourceGLSL*);

        /**
         * @brief Destroy the OBDShaderProgram object
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