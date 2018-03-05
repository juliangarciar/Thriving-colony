#ifndef RESOURCEGLSL_H
#define RESOURCEGLSL_H

#include "Resource.h"

enum ShaderType {
    VERTEX,
    FRAGMENT
};

class ResourceGLSL : public Resource {
    public:
        ResourceGLSL();
        ~ResourceGLSL();

        void load(const char *path);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        GLuint getShaderID();
    private:

        GLuint shaderID;
        ShaderType type;
};

#endif