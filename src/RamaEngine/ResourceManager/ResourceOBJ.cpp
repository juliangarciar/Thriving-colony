#include "ResourceOBJ.h"

#include <objloader/OBJ_Loader.h>
#include <objloader/vboindexer.hpp>
#include <glm/glm.hpp>

ResourceOBJ::ResourceOBJ(){

}

ResourceOBJ::~ResourceOBJ(){
    
}

void ResourceOBJ::load(const char *path){
    setIdentifier(path);
    objl::Loader loader;
    bool loadout = loader.LoadFile(path);
    if (!loadout) {
        std::cout << "Error al abrir el fichero " << path << std::endl;
        exit(0);
    }

    defaultMaterialPath = loader.pathToMaterial;

    for (int i = 0; i < loader.LoadedMeshes.size(); i++) {
        // Copy one of the loaded meshes to be our current mesh
        objl::Mesh curMesh = loader.LoadedMeshes[i];

        ResourceMesh *tempMesh = new ResourceMesh(curMesh.MeshName);

        std::vector<f32> vbo;

        for (int j = 0; j < curMesh.Vertices.size(); j++) {
            vbo.push_back(curMesh.Vertices[j].Position.X);
            vbo.push_back(curMesh.Vertices[j].Position.Y);
            vbo.push_back(curMesh.Vertices[j].Position.Z);
            vbo.push_back(curMesh.Vertices[j].Normal.X);
            vbo.push_back(curMesh.Vertices[j].Normal.Y);
            vbo.push_back(curMesh.Vertices[j].Normal.Z);
            vbo.push_back(curMesh.Vertices[j].TextureCoordinate.X);
            vbo.push_back(1.0f - curMesh.Vertices[j].TextureCoordinate.Y);
        }

        tempMesh->setVBO(vbo);
        tempMesh->setIndices(curMesh.Indices);
        tempMesh->setDefaultMaterialName(curMesh.MeshMaterial.name);

        meshArray.insert(std::pair<std::string, ResourceMesh*>(curMesh.MeshName, tempMesh));
    }
}

void ResourceOBJ::release(){
    for (std::map<std::string, ResourceMesh*>::iterator it = meshArray.begin(); it != meshArray.end(); ++it){
        delete it->second;
    }
    meshArray.clear();
}

void ResourceOBJ::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceOBJ::getIdentifier(){
    return identifier;
}

std::map<std::string, ResourceMesh*> *ResourceOBJ::getResource(){
    return &meshArray;
}

std::string ResourceOBJ::getDefaultMaterialPath(){
    return defaultMaterialPath;
}