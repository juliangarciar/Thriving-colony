#include "TResourceMesh.h"

TResourceMesh::TResourceMesh(std::string) {
    vertices = new std::vector<TVertex*>();
    indices = new std::vector<u32>();
}

TResourceMesh::~TResourceMesh() {

}

void addVertex(TVertex *v){
    vertices.push_back(v);
}

void addIndex(u32 i){
    indices.push_back(i);
}

void setMaterial(TMaterial *m){
    material = m;
}

std::vector<TVertex*> *getVertices(){
    return vertices;
}

std::vector<u32> getIndices(){
    return indices;
}

TMaterial *getMaterial(){
    return material;
}