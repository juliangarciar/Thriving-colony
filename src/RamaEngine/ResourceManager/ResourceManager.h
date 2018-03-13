#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "../RETypes.h"

#include "Resource.h"

#include "ResourceOBJ.h"
#include "ResourceJSON.h"
#include "ResourceGLSL.h"
#include "ResourceBMP.h"

class ResourceManager {
    public:
        ResourceManager();
        ~ResourceManager();

        /**
         * @brief 
         * 
         */
        void Update();

        /**
         * @brief 
         * 
         */
        void loadResource(std::string, bool = true);

        /**
         * @brief Get the Resource object
         * 
         * @return Resource* 
         */
        Resource *getResource(std::string, bool = false);
    private:
        /**
         * @brief 
         * 
         */
        void load(std::string);

        /**
         * @brief 
         * 
         */
        void push(std::string);

        std::map<std::string, Resource *> resources;
        std::queue<std::thread> threads;
        std::vector<std::string> supportedFormats;
};

#endif