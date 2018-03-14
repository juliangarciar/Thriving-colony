#include "ResourceOBJ.h"

#include <objloader/OBJ_Loader.h>
#include <objloader/vboindexer.hpp>
#include <glm/glm.hpp>

#include "../Graphics/TMaterial.h"

ResourceOBJ::ResourceOBJ(ResourceManager *rm){
    loadedBy = rm;
}

ResourceOBJ::~ResourceOBJ(){
    
}

void ResourceOBJ::load(const char *path, bool sync){
    setIdentifier(path);
    objl::Loader loader;
    bool loadout = loader.LoadFile(path);
    if (!loadout) {
        std::cout << "Error al abrir el fichero " << path << std::endl;
        exit(0);
    }

    for (int i = 0; i < loader.LoadedMeshes.size(); i++) {
        // Copy one of the loaded meshes to be our current mesh
        objl::Mesh curMesh = loader.LoadedMeshes[i];

        TResourceMesh *tempMesh = new TResourceMesh(curMesh.MeshName);

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;
        std::vector<us32> indices;
        std::vector<glm::vec3> indexed_vertices;
        std::vector<glm::vec2> indexed_uvs;
        std::vector<glm::vec3> indexed_normals;

        for (int j = 0; j < curMesh.Vertices.size(); j++) {
            glm::vec3 position(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z);
			glm::vec3 normal(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z);
			glm::vec2 textureCoordinate(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y);

            vertices.push_back(position);
            normals.push_back(normal);
            uvs.push_back(textureCoordinate);
        }

        indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

        tempMesh->setVertices(indexed_vertices);
        tempMesh->setNormals(indexed_normals);
        tempMesh->setTextureCoordinates(indexed_uvs);
        tempMesh->setIndices(indices);

        TMaterial *tempMat = new TMaterial();
        tempMat -> setName(curMesh.MeshMaterial.name);
        tempMat -> setAmbientColor(glm::vec3(curMesh.MeshMaterial.Ka.X, curMesh.MeshMaterial.Ka.Y, curMesh.MeshMaterial.Ka.Z));
        tempMat -> setDiffuseColor(glm::vec3(curMesh.MeshMaterial.Kd.X, curMesh.MeshMaterial.Kd.Y, curMesh.MeshMaterial.Kd.Z));
        tempMat -> setSpecularColor(glm::vec3(curMesh.MeshMaterial.Ks.X, curMesh.MeshMaterial.Ks.Y, curMesh.MeshMaterial.Ks.Z));
        tempMat -> setSpecularExponent(curMesh.MeshMaterial.Ns);
        tempMat -> setOpticalDensity(curMesh.MeshMaterial.Ni);
        tempMat -> setDissolve(curMesh.MeshMaterial.d);
        tempMat -> setIllumination(curMesh.MeshMaterial.illum);

        if (curMesh.MeshMaterial.map_Ka != ""){
            ResourceIMG *tempResourceIMG = (ResourceIMG*)loadedBy->getResource(curMesh.MeshMaterial.map_Ka, sync);
            TTexture *tempTex = new TTexture(tempResourceIMG);
            tempMat -> setAmbientTextureMap(curMesh.MeshMaterial.map_Ka, tempTex);
        }

        if (curMesh.MeshMaterial.map_Kd != ""){
            ResourceIMG *tempResourceIMG = (ResourceIMG*)loadedBy->getResource(curMesh.MeshMaterial.map_Kd, sync);
            TTexture *tempTex = new TTexture(tempResourceIMG);
            tempMat -> setDiffuseTextureMap(curMesh.MeshMaterial.map_Kd, tempTex);
        }

        if (curMesh.MeshMaterial.map_Ks != ""){
            ResourceIMG *tempResourceIMG = (ResourceIMG*)loadedBy->getResource(curMesh.MeshMaterial.map_Ks, sync);
            TTexture *tempTex = new TTexture(tempResourceIMG);
            tempMat -> setSpecularTextureMap(curMesh.MeshMaterial.map_Ks, tempTex);
        }

        if (curMesh.MeshMaterial.map_d != ""){
            ResourceIMG *tempResourceIMG = (ResourceIMG*)loadedBy->getResource(curMesh.MeshMaterial.map_d, sync);
            TTexture *tempTex = new TTexture(tempResourceIMG);
            tempMat -> setAlphaTextureMap(curMesh.MeshMaterial.map_d, tempTex);
        }

        if (curMesh.MeshMaterial.map_bump != ""){
            ResourceIMG *tempResourceIMG = (ResourceIMG*)loadedBy->getResource(curMesh.MeshMaterial.map_bump, sync);
            TTexture *tempTex = new TTexture(tempResourceIMG);
            tempMat -> setBumpMap(curMesh.MeshMaterial.map_bump, tempTex);
        }
       
        tempMesh -> setMaterial(tempMat);

        objMesh.push_back(tempMesh);
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