#include "TResourceMesh.h"

TResourceMesh::TResourceMesh(std::string) {
    
}

TResourceMesh::~TResourceMesh() {

}

void TResourceMesh::addVertex(glm::vec3 v, glm::vec3 n, glm::vec2 t){
    vertices.push_back(v);
    normals.push_back(n);
    textureCoordinates.push_back(t);
}

void TResourceMesh::addIndex(u32 i){
    indices.push_back(i);
}

void TResourceMesh::setMaterial(TMaterial *m){
    material = m;
}

std::vector<glm::vec3> TResourceMesh::getVertices(){
    return vertices;
}

std::vector<glm::vec3> TResourceMesh::getNormals(){
    return normals;
}

std::vector<glm::vec2> TResourceMesh::getTextureCoordinates(){
    return textureCoordinates;
}

std::vector<u32> TResourceMesh::getIndices(){
    return indices;
}

TMaterial *TResourceMesh::getMaterial(){
    return material;
}