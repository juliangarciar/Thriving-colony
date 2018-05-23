#ifndef OBDSOURCEGLSL_H
#define OBDSOURCEGLSL_H

#include "Resource.h"
#include "ResourceManager.h"

class ResourceGLSL : public Resource {
    public:
        /**
         * @brief Construct a new Resource G L S L object
         * 
         */
        ResourceGLSL();
        /**
         * @brief Destroy the Resource G L S L object
         * 
         */
        ~ResourceGLSL();
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
         * @brief Get the source code of the shader
         * 
         * @return std::string* 
         */
        std::string *getShaderCode();
        /**
         * @brief Returns the type of the shader
         * 
         * @return OBDEnums::ShaderType 
         */
        OBDEnums::ShaderType getShaderType();
    private:
        // SOurce code
        std::string shaderCode;
        // Type of shader (vertex or fragment)
        OBDEnums::ShaderType type;
        
};

#endif