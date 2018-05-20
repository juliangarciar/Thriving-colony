#include "ResourceMTL.h"

#define NAMESPACE mtl_objl
#include <objloader/OBJ_Loader.h>

ResourceMTL::ResourceMTL(){
	materialArray = new std::map<std::string, ResourceMaterial*>();
}

ResourceMTL::~ResourceMTL(){
	for (std::map<std::string, ResourceMaterial*>::iterator it = materialArray->begin(); it != materialArray->end(); ++it){
		delete it->second;
	}
	materialArray->clear();
    delete materialArray;
	materialArray = nullptr;
}

void ResourceMTL::load(const char *path){
    setIdentifier(path);
    mtl_objl::Loader loader;

    bool loadout = loader.LoadMaterials(path);
    if (!loadout) {
        std::cout << "Error al abrir el fichero " << path << std::endl;
        exit(0);
    }

	std::string p(path);

	size_t last = p.rfind("/");
	std::string ret = p.substr(0,last+1);

    for (i32 i = 0; i < loader.LoadedMaterials.size(); i++) {
        // Copy one of the loaded meshes to be our current mesh
        mtl_objl::Material curMat = loader.LoadedMaterials[i];

        ResourceMaterial *tempMat = new ResourceMaterial();

        tempMat -> materialName = curMat.name;
        tempMat -> ambientColor = glm::vec3(curMat.Ka.X, curMat.Ka.Y, curMat.Ka.Z);
        tempMat -> diffuseColor = glm::vec3(curMat.Kd.X, curMat.Kd.Y, curMat.Kd.Z);
        tempMat -> specularColor = glm::vec3(curMat.Ks.X, curMat.Ks.Y, curMat.Ks.Z);
        tempMat -> specularExponent = curMat.Ns;
        tempMat -> opticalDensity = curMat.Ni;
        tempMat -> dissolve = curMat.d;
        tempMat -> illumination = curMat.illum;
        if (curMat.map_Kd != "") tempMat -> diffuseTextureMap = ret+curMat.map_Kd;
        if (curMat.map_Ka != "") tempMat -> ambientOclusionsTextureMap = ret+curMat.map_Ka;
        if (curMat.map_Ks != "") tempMat -> specularTextureMap = ret+curMat.map_Ks;
        if (curMat.map_d != "") tempMat -> alphaTextureMap = ret+curMat.map_d;
        
        materialArray->insert(std::pair<std::string, ResourceMaterial*>(curMat.name, tempMat));
    }
}

void ResourceMTL::release(){
    materialArray->clear();
}

void ResourceMTL::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceMTL::getIdentifier(){
    return identifier;
}

std::map<std::string, ResourceMaterial*> *ResourceMTL::getResource(){
    return materialArray;
}