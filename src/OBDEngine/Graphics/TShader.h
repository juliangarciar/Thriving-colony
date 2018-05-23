#ifndef TSHADER_H
#define TSHADER_H

#include "../OBDTypes.h"
#include "../ResourceManager/ResourceGLSL.h"

class TShader {
    public:
        /**
         * @brief Construct a new TShader object
         * 
         * @param s source file for the shader
         */
        TShader(ResourceGLSL *s);

        /**
         * @brief Destroy the TShader object
         * 
         */
        ~TShader();
        
        /**
         * @brief Get this shader's ID
         * 
         * @return GLuint ID
         */
        GLuint getShaderID();
    private:
        GLuint shaderID;
};
    
#endif