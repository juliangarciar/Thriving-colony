#ifndef RESOURCEMESH_H
#define RESOURCEMESH_H

#include "../../RETypes.h"

class ResourceMesh {
    public:
        ResourceMesh(std::string);
        ~ResourceMesh();

        void setVertices(std::vector<glm::vec3>);
        void setNormals(std::vector<glm::vec3>);
        void setUVs(std::vector<glm::vec2>);
        void setIndices(std::vector<us32>);

        void setDefaultMaterialName(std::string);

        std::vector<glm::vec3> getVertices();
        std::vector<glm::vec3> getNormals();
        std::vector<glm::vec2> getUVs();
        std::vector<us32> getIndices();

        std::string getDefaultMaterialName();
    private:
        std::string name;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;
        std::vector<us32> indices;

        std::string defaultMaterialName;
};

#endif