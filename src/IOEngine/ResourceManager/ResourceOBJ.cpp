#include "ResourceOBJ.h"

#include <objloader/OBJ_Loader.h>

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

    for (int i = 0; i < loader.LoadedMeshes.size(); i++) {
        // Copy one of the loaded meshes to be our current mesh
        objl::Mesh curMesh = loader.LoadedMeshes[i];

        TResourceMesh *tempMesh = new TResourceMesh(curMesh.MeshName);

        for (int j = 0; j < curMesh.Vertices.size(); j++) {
            Vector3<float> position(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z);
			Vector3<float> normal(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z);
			Vector2<float> textureCoordinate(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y);
            tempMesh -> addVertex(new TVertex(position.getVec3(), normal.getVec3(), textureCoordinate.getVec2()));
        }

        for (int j = 0; j < curMesh.Indices.size(); j++) {
            tempMesh -> addIndex(curMesh.Indices[j]);
        }

        TMaterial *tempMat = new TMaterial();
        tempMat -> setName(curMesh.MeshMaterial.name);
        tempMat -> setAmbientColor(Vector3<f32>(curMesh.MeshMaterial.Ka.X, curMesh.MeshMaterial.Ka.Y, curMesh.MeshMaterial.Ka.Z));
        tempMat -> setDiffuseColor(Vector3<f32>(curMesh.MeshMaterial.Kd.X, curMesh.MeshMaterial.Kd.Y, curMesh.MeshMaterial.Kd.Z));
        tempMat -> setSpecularColor(Vector3<f32>(curMesh.MeshMaterial.Ks.X, curMesh.MeshMaterial.Ks.Y, curMesh.MeshMaterial.Ks.Z));
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