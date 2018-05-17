#ifndef TSHADER_H
#define TSHADER_H

#include "../OBDTypes.h"
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