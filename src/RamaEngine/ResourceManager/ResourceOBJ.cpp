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
        tempMesh->setUVs(indexed_uvs);
        tempMesh->setIndices(indices);
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