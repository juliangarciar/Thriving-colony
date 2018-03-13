#ifndef TSHADER_H
#define TSHADER_H

#include "../RETypes.h"
#include "../ResourceManager/ResourceGLSL.h"

class TShader {
    public:
        TShader(ResourceGLSL *s);
        ~TShader();
        
        GLuint getShaderID();
    private:
        GLuint shaderID;
};
    
#endif