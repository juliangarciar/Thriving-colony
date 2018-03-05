#ifndef TRESOURCEMESH_H
#define TRESOURCEMESH_H

#include "../RETypes.h"
#include "TMaterial.h"

class TResourceMesh {
    public:
        TResourceMesh(std::string);
        ~TResourceMesh();

        void addVertex(glm::vec3, glm::vec3, glm::vec2);
        void addIndex(u32);

        void setMaterial(TMaterial *);

        std::vector<glm::vec3> getVertices();
        std::vector<glm::vec3> getNormals();
        std::vector<glm::vec2> getTextureCoordinates();
        std::vector<u32> getIndices();

        TMaterial *getMaterial();
    private:
        std::string name;
        TMaterial *material;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> textureCoordinates;
        std::vector<u32> indices;
};

#endif