#ifndef OBDSOURCEMANAGER_H
#define OBDSOURCEMANAGER_H

#include "../OBDTypes.h"

#include "Resource.h"

class ResourceManager {
    public:
        /**
         * @brief Construct a new Resource Manager object
         * 
         */
        ResourceManager();
        /**
         * @brief Destroy the Resource Manager object
         * 
         */
        ~ResourceManager();

		/**
		 * @brief manage the threads currently alive
		 * 
		 */
		void Update();

        /**
         * @brief load a resource asynchronously
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
         * @brief load the resource indicated with the path only if 
         * its format is supported
         * 
         */
        void load(std::string);

        /**
         * @brief pushes a thread to load a resource asynchronously only if the are 
         * available threads
         * 
         */
        void push(std::string);

        // Asynchronous loading
		i32 maxThreads;
		i32 currentThreads;

        // Resource types
        std::map<std::string, Resource *> resources;
        std::queue<std::string> paths;
        // Currently supported formats.
        std::vector<std::string> supportedFormats;
};

#endif