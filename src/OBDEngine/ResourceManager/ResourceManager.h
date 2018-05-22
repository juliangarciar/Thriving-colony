#ifndef OBDSOURCEMANAGER_H
#define OBDSOURCEMANAGER_H

#include "../OBDTypes.h"

#include "Resource.h"

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

		i32 maxThreads;
		i32 currentThreads;

        std::map<std::string, Resource *> resources;
        std::queue<std::string> paths;
        std::vector<std::string> supportedFormats;
};

#endif