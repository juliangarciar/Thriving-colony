#ifndef RESHADERPROGRAM_H
#define RESHADERPROGRAM_H

#include <GL/glew.h>
#include "RETypes.h"
#include "REEnums.h"

#include "Graphics/TShader.h"

class REShaderProgram {
    public:
        /**
         * @brief 
         * @param shader
         * @param shader
         */
        REShaderProgram(ResourceGLSL*, ResourceGLSL*);

        /**
         * @brief 
         * 
         */
        ~REShaderProgram();

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