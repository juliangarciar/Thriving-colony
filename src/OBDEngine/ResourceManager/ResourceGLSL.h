#ifndef RESOURCEGLSL_H
#define RESOURCEGLSL_H

#include "Resource.h"
#include "ResourceManager.h"

class ResourceGLSL : public Resource {
    public:
        ResourceGLSL();
        ~ResourceGLSL();

        void load(const char *path);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        std::string *getShaderCode();
        OBDEEnums::ShaderType getShaderType();
    private:
        std::string shaderCode;
        OBDEEnums::ShaderType type;
        
};

#endif