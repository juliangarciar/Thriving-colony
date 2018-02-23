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

    for (int i = 0; i < loader.LoadedMeshes.size(); i++) {
        // Copy one of the loaded meshes to be our current mesh
        objl::Mesh curMesh = loader.LoadedMeshes[i];

        TResourceMesh *tempMesh = new TResourceMesh(curMesh.MeshName);

        for (int j = 0; j < curMesh.Vertices.size(); j++) {
            Vector3<float> position(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z);
			Vector3<float> normal(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z);
			Vector2<float> textureCoordinate(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y);
            tempMesh->addVertex(new TVertex(position.getVec3(), normal.getVec3(), textureCoordinate.getVec2()));
        }

        for (int j = 0; j < curMesh.Indices.size(); j++) {
            tempMesh->addIndex(curMesh.Indices[j]);
        }
        /*
        file << "Material: " << curMesh.MeshMaterial.name << "\n";
        file << "Ambient Color: " << curMesh.MeshMaterial.Ka.X << ", " << curMesh.MeshMaterial.Ka.Y << ", " << curMesh.MeshMaterial.Ka.Z << "\n";
        file << "Diffuse Color: " << curMesh.MeshMaterial.Kd.X << ", " << curMesh.MeshMaterial.Kd.Y << ", " << curMesh.MeshMaterial.Kd.Z << "\n";
        file << "Specular Color: " << curMesh.MeshMaterial.Ks.X << ", " << curMesh.MeshMaterial.Ks.Y << ", " << curMesh.MeshMaterial.Ks.Z << "\n";
        file << "Specular Exponent: " << curMesh.MeshMaterial.Ns << "\n";
        file << "Optical Density: " << curMesh.MeshMaterial.Ni << "\n";
        file << "Dissolve: " << curMesh.MeshMaterial.d << "\n";
        file << "Illumination: " << curMesh.MeshMaterial.illum << "\n";
        file << "Ambient Texture Map: " << curMesh.MeshMaterial.map_Ka << "\n";
        file << "Diffuse Texture Map: " << curMesh.MeshMaterial.map_Kd << "\n";
        file << "Specular Texture Map: " << curMesh.MeshMaterial.map_Ks << "\n";
        file << "Alpha Texture Map: " << curMesh.MeshMaterial.map_d << "\n";
        file << "Bump Map: " << curMesh.MeshMaterial.map_bump << "\n";*/
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