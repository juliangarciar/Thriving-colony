#ifndef TRESOURCEMESH_H
#define TRESOURCEMESH_H

#include <vector>
#include <Types.h>
#include <OurEngine/TMaterial.h>
#include <OurEngine/TVertex.h>

class TResourceMesh {
    public:
        TResourceMesh(std::string);
        ~TResourceMesh();

        void addVertex(TVertex *);
        void addIndex(u32);

        void setMaterial(TMaterial *);

        std::vector<TVertex*> *getVertices();
        std::vector<u32> getIndices();
        TMaterial *getMaterial();
    private:
        std::string name;
        TMaterial *material;
        std::vector<TVertex*> *vertices;
        std::vector<u32> *indices;
};

#endif