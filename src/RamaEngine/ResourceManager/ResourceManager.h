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

        void Update();

        void loadResource(std::string, bool = true);

        Resource *getResource(std::string, bool = false);
    private:
        void load(std::string);
        void push(std::string);

        std::map<std::string, Resource *> resources;
        std::queue<std::thread> threads;
};

#endif