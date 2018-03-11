#ifndef RESHADERPROGRAM_H
#define RESHADERPROGRAM_H

#include <GL/gl.h>
#include "RETypes.h"
#include "REEnums.h"

#include "Graphics/TRoot.h"
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
         * @brief Get the Root Entity object
         * 
         * @return GLuint 
         */
        TRoot *getRootEntity();

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
        TRoot *rootEntity;
};

#endif