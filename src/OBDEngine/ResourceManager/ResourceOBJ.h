#ifndef OBDSOURCEOBJ_H
#define OBDSOURCEOBJ_H

#include "Resource.h"
#include "ResourceManager.h"

struct BoundingBox {
    glm::vec3 min;
    glm::vec3 max;
    glm::vec3 size;
    glm::vec3 center;
};

struct ResourceMesh {
    std::string name;

    std::vector<f32> vbo;
    std::vector<us32> indices;

    std::string defaultMaterialName;
};

class ResourceOBJ : public Resource {
    public:
        ResourceOBJ();
        ~ResourceOBJ();

        void load(const char *path);
        void release();

        void setIdentifier(const char *);
        const char *getIdentifier();

        std::map<std::string, ResourceMesh> getResource();

        std::string getDefaultMaterialPath();
    private:
        std::map<std::string, ResourceMesh> meshArray;
        std::string defaultMaterialPath;
};

#endif