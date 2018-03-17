#include "ResourceMesh.h"

ResourceMesh::ResourceMesh(std::string n) {
    name = n;
}

ResourceMesh::~ResourceMesh() {

}

void ResourceMesh::setVertices(std::vector<glm::vec3> v){
    vertices = v;
}

void ResourceMesh::setNormals(std::vector<glm::vec3> v){
    normals = v;
}

void ResourceMesh::setUVs(std::vector<glm::vec2> v){
    uvs = v;
}

void ResourceMesh::setIndices(std::vector<us32> v){
    indices = v;
}

void ResourceMesh::setDefaultMaterialName(std::string d){
    defaultMaterialName = d;
}

std::vector<glm::vec3> ResourceMesh::getVertices(){
    return vertices;
}

std::vector<glm::vec3> ResourceMesh::getNormals(){
    return normals;
}

std::vector<glm::vec2> ResourceMesh::getUVs(){
    return uvs;
}

std::vector<us32> ResourceMesh::getIndices(){
    return indices;
}

std::string ResourceMesh::getDefaultMaterialName(){
    return defaultMaterialName;
}