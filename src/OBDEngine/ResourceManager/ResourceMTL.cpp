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

        ResourceMaterial *tempMat = new ResourceMaterial();

        tempMat -> setName(curMat.name);
        tempMat -> setAmbientColor(glm::vec3(curMat.Ka.X, curMat.Ka.Y, curMat.Ka.Z));
        tempMat -> setDiffuseColor(glm::vec3(curMat.Kd.X, curMat.Kd.Y, curMat.Kd.Z));
        tempMat -> setSpecularColor(glm::vec3(curMat.Ks.X, curMat.Ks.Y, curMat.Ks.Z));
        tempMat -> setSpecularExponent(curMat.Ns);
        tempMat -> setOpticalDensity(curMat.Ni);
        tempMat -> setDissolve(curMat.d);
        tempMat -> setIllumination(curMat.illum);
        tempMat -> setAmbientTextureMap(curMat.map_Ka);
        tempMat -> setDiffuseTextureMap(curMat.map_Kd);
        tempMat -> setSpecularTextureMap(curMat.map_Ks);
        tempMat -> setAlphaTextureMap(curMat.map_d);
        tempMat -> setBumpMap(curMat.map_bump);
        
        materialArray.insert(std::pair<std::string, ResourceMaterial*>(curMat.name, tempMat));
    }
}

void ResourceMTL::release(){
    for (std::map<std::string, ResourceMaterial*>::iterator it = materialArray.begin(); it != materialArray.end(); ++it){
        delete it->second;
    }
    materialArray.clear();
}

void ResourceMTL::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceMTL::getIdentifier(){
    return identifier;
}

std::map<std::string, ResourceMaterial*> *ResourceMTL::getResource(){
    return &materialArray;
}