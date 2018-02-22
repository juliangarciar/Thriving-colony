#include "ResourceOBJ.h"

ResourceOBJ::ResourceOBJ(){
    objMesh = new std::vector<TResourceMesh*>();
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

    for (int i = 0; i < Loader.LoadedMeshes.size(); i++) {
        // Copy one of the loaded meshes to be our current mesh
        objl::Mesh curMesh = Loader.LoadedMeshes[i];

        TResourceMesh *tempMesh = new TResourceMesh(curMesh.MeshName);
        // ToDo
    }
}

void ResourceOBJ::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceOBJ::getIdentifier(){
    return identifier;
}

std::vector<TResourceMesh*> *ResourceOBJ::getOBJMesh(){
    return objMesh;
}