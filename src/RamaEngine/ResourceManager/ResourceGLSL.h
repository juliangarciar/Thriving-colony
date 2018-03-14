#ifndef RESOURCEGLSL_H
#define RESOURCEGLSL_H

#include "Resource.h"
#include "ResourceManager.h"

class ResourceGLSL : public Resource {
    public:
        ResourceGLSL(ResourceManager *);
        ~ResourceGLSL();

        void load(const char *path, bool sync);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        std::string *getShaderCode();
        REEnums::ShaderType getShaderType();
    private:
        std::string shaderCode;
        REEnums::ShaderType type;
        ResourceManager *loadedBy;
};

#endif