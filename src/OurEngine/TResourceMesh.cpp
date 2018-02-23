#include "TResourceMesh.h"

TResourceMesh::TResourceMesh(std::string) {
    
}

TResourceMesh::~TResourceMesh() {

}

void TResourceMesh::addVertex(TVertex *v){
    vertices.push_back(v);
}

void TResourceMesh::addIndex(u32 i){
    indices.push_back(i);
}

void TResourceMesh::setMaterial(TMaterial *m){
    material = m;
}

std::vector<TVertex*> TResourceMesh::getVertices(){
    return vertices;
}

std::vector<u32> TResourceMesh::getIndices(){
    return indices;
}

TMaterial *TResourceMesh::getMaterial(){
    return material;
}