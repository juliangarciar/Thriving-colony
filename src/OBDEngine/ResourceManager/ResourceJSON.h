#ifndef OBDSOURCEJSON_H
#define OBDSOURCEJSON_H

#include "Resource.h"
#include "ResourceManager.h"

#include <json/json.hpp>

using json = nlohmann::json; 

class ResourceJSON : public Resource {
    public:
        /**
         * @brief Construct a new Resource J S O N object
         * 
         */
        ResourceJSON();
        /**
         * @brief Destroy the Resource J S O N object
         * 
         */
        ~ResourceJSON();
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
         * @brief returns the JSON file
         * 
         * @return json* json file
         */
        json *getJSON();
    private:
        json j;
        
};

#endif