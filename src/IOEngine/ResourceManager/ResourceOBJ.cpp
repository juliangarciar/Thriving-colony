#include "ResourceOBJ.h"

#include <OurEngine/TMaterial.h>
#include <objloader/OBJ_Loader.h>
#include <glm/glm.hpp>

ResourceOBJ::ResourceOBJ(){
    
}

ResourceOBJ::~ResourceOBJ(){
    
}

void ResourceOBJ::load(const char *path){
    setIdentifier(path);
    objl::Loader loader;
        std::cout << "Os" << std::endl;
    bool loadout = loader.LoadFile(path);
    if (!loadout) {
        std::cout << "Error al abrir el fichero " << path << std::endl;
        exit(0);
    }
        std::cout << "Osd" << std::endl;

    for (int i = 0; i < loader.LoadedMeshes.size(); i++) {
        std::cout << "OE" << std::endl;
        // Copy one of the loaded meshes to be our current mesh
        objl::Mesh curMesh = loader.LoadedMeshes[i];

        TResourceMesh *tempMesh = new TResourceMesh(curMesh.MeshName);

        for (int j = 0; j < curMesh.Vertices.size(); j++) {
            glm::vec3 position(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z);
			glm::vec3 normal(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z);
			glm::vec2 textureCoordinate(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y);
            tempMesh->addVertex(position, normal, textureCoordinate);
        }

        for (int j = 0; j < curMesh.Indices.size(); j++) {
            tempMesh -> addIndex(curMesh.Indices[j]);
        }

        std::cout << "I" << std::endl;

        TMaterial *tempMat = new TMaterial();
        tempMat -> setName(curMesh.MeshMaterial.name);
        tempMat -> setAmbientColor(glm::vec3(curMesh.MeshMaterial.Ka.X, curMesh.MeshMaterial.Ka.Y, curMesh.MeshMaterial.Ka.Z));
        tempMat -> setDiffuseColor(glm::vec3(curMesh.MeshMaterial.Kd.X, curMesh.MeshMaterial.Kd.Y, curMesh.MeshMaterial.Kd.Z));
        tempMat -> setSpecularColor(glm::vec3(curMesh.MeshMaterial.Ks.X, curMesh.MeshMaterial.Ks.Y, curMesh.MeshMaterial.Ks.Z));
        tempMat -> setSpecularExponent(curMesh.MeshMaterial.Ns);
        tempMat -> setOpticalDensity(curMesh.MeshMaterial.Ni);
        tempMat -> setDissolve(curMesh.MeshMaterial.d);
        tempMat -> setIllumination(curMesh.MeshMaterial.illum);
        tempMat -> setAmbientTextureMap(curMesh.MeshMaterial.map_Ka);
        tempMat -> setDiffuseTextureMap(curMesh.MeshMaterial.map_Kd);
        tempMat -> setSpecularTextureMap(curMesh.MeshMaterial.map_Ks);
        tempMat -> setAlphaTextureMap(curMesh.MeshMaterial.map_d);
        tempMat -> setBumpMap(curMesh.MeshMaterial.map_bump);

        tempMesh ->setMaterial(tempMat);
        std::cout << "U" << std::endl;
    }
}

void ResourceOBJ::release(){
    for (int i=0; i < objMesh.size(); i++){
        delete objMesh.at(i);
    }
    objMesh.clear();
}

void ResourceOBJ::setIdentifier(const char *i){
    identifier = i;
}

const char *ResourceOBJ::getIdentifier(){
    return identifier;
}

std::vector<TResourceMesh*> *ResourceOBJ::getResource(){
    return &objMesh;
}