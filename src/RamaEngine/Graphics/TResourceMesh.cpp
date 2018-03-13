#include "TResourceMesh.h"

TResourceMesh::TResourceMesh(std::string n) {
    name = n;
}

TResourceMesh::~TResourceMesh() {

}

void TResourceMesh::setVertices(std::vector<glm::vec3> v){
    vertices = v;
}

void TResourceMesh::setNormals(std::vector<glm::vec3> v){
    normals = v;
}

void TResourceMesh::setTextureCoordinates(std::vector<glm::vec2> v){
    textureCoordinates = v;
}

void TResourceMesh::setIndices(std::vector<us32> v){
    indices = v;
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

std::vector<us32> TResourceMesh::getIndices(){
    return indices;
}

TMaterial *TResourceMesh::getMaterial(){
    return material;
}