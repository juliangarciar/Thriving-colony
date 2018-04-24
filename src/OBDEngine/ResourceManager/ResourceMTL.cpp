#include "ResourceMTL.h"

#define NAMESPACE mtl_objl
#include <objloader/OBJ_Loader.h>

ResourceMTL::ResourceMTL(){

}

ResourceMTL::~ResourceMTL(){
    
}

void ResourceMTL::load(const char *path){
    setIdentifier(path);
    mtl_objl::Loader loader;

    bool loadout = loader.LoadMaterials(path);
    if (!loadout) {
        std::cout << "Error al abrir el fichero " << path << std::endl;
        exit(0);
    }

    for (int i = 0; i < loader.LoadedMaterials.size(); i++) {
        // Copy one of the loaded meshes to be our current mesh
        mtl_objl::Material curMat = loader.LoadedMaterials[i];

        ResourceMaterial tempMat;

        tempMat.materialName = curMat.name;
        tempMat.ambientColor = glm::vec3(curMat.Ka.X, curMat.Ka.Y, curMat.Ka.Z);
        tempMat.diffuseColor = glm::vec3(curMat.Kd.X, curMat.Kd.Y, curMat.Kd.Z);
        tempMat.specularColor = glm::vec3(curMat.Ks.X, curMat.Ks.Y, curMat.Ks.Z);
        tempMat.specularExponent = curMat.Ns;
        tempMat.opticalDensity = curMat.Ni;
        tempMat.dissolve = curMat.d;
        tempMat.illumination = curMat.illum;
        tempMat.ambientTextureMap = curMat.map_Ka;
        tempMat.diffuseTextureMap = curMat.map_Kd;
        tempMat.specularTextureMap = curMat.map_Ks;
        tempMat.alphaTextureMap = curMat.map_d;
        tempMat.bumpMap = curMat.map_bump;
        
        materialArray.insert(std::pair<std::string, ResourceMaterial>(curMat.name, tempMat));
    }
}

void ResourceMTL::release(){
    materialArray.clear();
}

void ResourceMTL::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceMTL::getIdentifier(){
    return identifier;
}

std::map<std::string, ResourceMaterial> ResourceMTL::getResource(){
    return materialArray;
}