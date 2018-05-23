#ifndef OBDSOURCEMTL_H
#define OBDSOURCEMTL_H

#include "Resource.h"
#include "ResourceManager.h"

struct ResourceMaterial{
    std::string materialName;
    // Material properties
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
    
    f32 specularExponent;
    f32 opticalDensity;
    f32 dissolve;
    i32 illumination;
    // Path to the different textures
    std::string diffuseTextureMap;
    std::string ambientOclusionsTextureMap;
    std::string specularTextureMap;
    std::string alphaTextureMap;
};

class ResourceMTL : public Resource {
    public:
        /**
         * @brief Construct a new Resource M T L object
         * 
         */
        ResourceMTL();
        /**
         * @brief Destroy the Resource M T L object
         * 
         */
        ~ResourceMTL();
        /**
         * @brief load the obj file
         * 
         * @param path path to file
         */
        void load(const char *path);
        /**
         * @brief release this resource, freeing up the memory it occupied.
         * 
         */
        void release();
        /**
         * @brief Set the ID
         * 
         */
        void setIdentifier(const char *);
        /**
         * @brief returns the id of the resource
         * 
         * @return const char* 
         */
        const char *getIdentifier();
        /**
         * @brief Get the Resource object
         * 
         * @return std::map<std::string, ResourceMesh*>* mesh Array wth all the data relative to this resource
         */
        std::map<std::string, ResourceMaterial*> *getResource();
    private:
        std::map<std::string, ResourceMaterial*> *materialArray;
        
};

#endif