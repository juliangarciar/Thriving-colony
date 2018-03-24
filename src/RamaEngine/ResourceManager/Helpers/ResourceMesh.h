#ifndef RESOURCEMESH_H
#define RESOURCEMESH_H

#include "../../RETypes.h"

class ResourceMesh {
    public:
        ResourceMesh(std::string);
        ~ResourceMesh();

        void setVBO(std::vector<f32>);
        void setIndices(std::vector<us32>);

        void setDefaultMaterialName(std::string);

        std::vector<f32> getVBO();
        std::vector<us32> getIndices();

        std::string getName();
        std::string getDefaultMaterialName();
    private:
        std::string name;

        std::vector<f32> vbo;
        std::vector<us32> indices;

        std::string defaultMaterialName;
};

#endif