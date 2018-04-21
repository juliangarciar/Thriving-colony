#include "ResourceOBJ.h"

#include <objloader/OBJ_Loader.h>
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

        ResourceMesh tempMesh;

        std::vector<f32> vbo;

        vbo.reserve(curMesh.Vertices.size() * 8);

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

        tempMesh.name = curMesh.MeshName;
        tempMesh.vbo = vbo;
        tempMesh.indices = curMesh.Indices;
        tempMesh.defaultMaterialName = curMesh.MeshMaterial.name;

        meshArray.insert(std::pair<std::string, ResourceMesh>(curMesh.MeshName, tempMesh));
    }
}

void ResourceOBJ::release(){
    meshArray.clear();
}

void ResourceOBJ::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceOBJ::getIdentifier(){
    return identifier;
}

std::map<std::string, ResourceMesh> ResourceOBJ::getResource(){
    return meshArray;
}

std::string ResourceOBJ::getDefaultMaterialPath(){
    return defaultMaterialPath;
}