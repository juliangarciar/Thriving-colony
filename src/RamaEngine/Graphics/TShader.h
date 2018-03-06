#ifndef TSHADER_H
#define TSHADER_H

#include "../RETypes.h"
#include "../ResourceManager/ResourceGLSL.h"

class TShader {
    public:
        TShader();
        ~TShader();

        void setShader(ResourceGLSL *);
        
        GLuint getShaderID();
    private:
        GLuint shaderID;
};
    
#endif