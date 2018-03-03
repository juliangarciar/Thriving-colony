#ifndef RESOURCEGLSL_H
#define RESOURCEGLSL_H

#include <vector>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

#include "Resource.h"
#include <Types.h>

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