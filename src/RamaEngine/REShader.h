#ifndef RESHADER_H
#define RESHADER_H

#include <GL/glew.h>
#include "RETypes.h"
#include "REEnums.h"

#include "Graphics/TShader.h"

class REShader {
    public:
        /**
         * @brief 
         * @param path ruta
         */
        REShader(ResourceGLSL*, GLuint);

        /**
         * @brief 
         * 
         */
        ~REShader();

        TShader *loadShader();
    private:
        GLuint pid;
        TShader *shader;
};

#endif