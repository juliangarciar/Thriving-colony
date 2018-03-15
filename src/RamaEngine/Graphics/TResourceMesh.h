#ifndef TRESOURCEMESH_H
#define TRESOURCEMESH_H

#include "../RETypes.h"
#include "TMaterial.h"

class TResourceMesh {
    public:
        TResourceMesh(std::string);
        ~TResourceMesh();

        void setVertices(std::vector<glm::vec3>);
        void setNormals(std::vector<glm::vec3>);
        void setTextureCoordinates(std::vector<glm::vec2>);
        void setIndices(std::vector<us32>);

        void setMaterial(TMaterial *);

        std::vector<glm::vec3> getVertices();
        std::vector<glm::vec3> getNormals();
        std::vector<glm::vec2> getTextureCoordinates();
        std::vector<us32> getIndices();

        TMaterial *getMaterial();
    private:
        std::string name;
        TMaterial *material;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> textureCoordinates;
        std::vector<us32> indices;
};

#endif