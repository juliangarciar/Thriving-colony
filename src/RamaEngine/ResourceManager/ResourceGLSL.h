#ifndef RESOURCEGLSL_H
#define RESOURCEGLSL_H

#include "Resource.h"

class ResourceGLSL : public Resource {
    public:
        ResourceGLSL();
        ~ResourceGLSL();

        void load(const char *path);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        std::string getShaderCode();
        REEnums::ShaderType getShaderType();
    private:
        std::string shaderCode;
        REEnums::ShaderType type;
};

#endif