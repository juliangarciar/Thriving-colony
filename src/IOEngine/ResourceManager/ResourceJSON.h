#ifndef RESOURCEJSON_H
#define RESOURCEJSON_H

#include <fstream>
#include <json/json.hpp>
#include "Resource.h"
#include <Types.h>
 
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