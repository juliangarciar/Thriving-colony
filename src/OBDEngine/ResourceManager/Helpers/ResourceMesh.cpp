#include "ResourceMesh.h"

ResourceMesh::ResourceMesh(std::string n) {
    name = n;
}

ResourceMesh::~ResourceMesh() {

}

void ResourceMesh::setVBO(std::vector<f32> v){
    vbo = v;
}

void ResourceMesh::setIndices(std::vector<us32> v){
    indices = v;
}

void ResourceMesh::setDefaultMaterialName(std::string d){
    defaultMaterialName = d;
}

std::vector<f32> ResourceMesh::getVBO(){
    return vbo;
}

std::vector<us32> ResourceMesh::getIndices(){
    return indices;
}

std::string ResourceMesh::getDefaultMaterialName(){
    return defaultMaterialName;
}

std::string ResourceMesh::getName(){
    return name;
}