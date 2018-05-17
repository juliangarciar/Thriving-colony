#ifndef OBDSOURCEMTL_H
#define OBDSOURCEMTL_H

#include "Resource.h"
#include "ResourceManager.h"

struct ResourceMaterial{
    std::string materialName;
    
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
    
    f32 specularExponent;
    f32 opticalDensity;
    f32 dissolve;
    i32 illumination;

    std::string diffuseTextureMap;
    std::string ambientOclusionsTextureMap;
    std::string specularTextureMap;
    std::string alphaTextureMap;
    std::string bumpMap;
};

class ResourceMTL : public Resource {
    public:
        ResourceMTL();
        ~ResourceMTL();

        void load(const char *path);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        std::map<std::string, ResourceMaterial*> *getResource();
    private:
        std::map<std::string, ResourceMaterial*> *materialArray;
        
};

#endif