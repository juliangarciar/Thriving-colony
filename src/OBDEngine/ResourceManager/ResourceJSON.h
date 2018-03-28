#ifndef OBDSOURCEJSON_H
#define OBDSOURCEJSON_H

#include "Resource.h"
#include "ResourceManager.h"

#include <json/json.hpp>

using json = nlohmann::json; 

class ResourceJSON : public Resource {
    public:
        ResourceJSON();
        ~ResourceJSON();
 
        void load(const char *path);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        json *getJSON();
    private:
        json j;
        
};

#endif