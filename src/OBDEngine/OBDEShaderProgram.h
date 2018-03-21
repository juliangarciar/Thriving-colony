#ifndef OBDESHADERPROGRAM_H
#define OBDESHADERPROGRAM_H

#include <GL/gl.h>
#include "OBDETypes.h"
#include "OBDEEnums.h"

#include "Graphics/TRoot.h"
#include "Graphics/TShader.h"

class OBDEShaderProgram {
    public:
        /**
         * @brief 
         * @param shader
         * @param shader
         */
        OBDEShaderProgram(ResourceGLSL*, ResourceGLSL*);

        /**
         * @brief 
         * 
         */
        ~OBDEShaderProgram();

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