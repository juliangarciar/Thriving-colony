#ifndef RESOURCEJSON_H
#define RESOURCEJSON_H

#include "Resource.h"
#include "ResourceManager.h"

#include <json/json.hpp>

using json = nlohmann::json; 

class ResourceJSON : public Resource {
    public:
        ResourceJSON(ResourceManager *);
        ~ResourceJSON();
 
        void load(const char *path, bool sync);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        json *getJSON();
    private:
        json j;
        ResourceManager *loadedBy;
};

#endif