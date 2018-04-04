#ifndef OBDSOURCEGLSL_H
#define OBDSOURCEGLSL_H

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
        OBDEnums::ShaderType getShaderType();
    private:
        std::string shaderCode;
        OBDEnums::ShaderType type;
        
};

#endif