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

        // Min and max bounding box
        glm::vec3 min(curMesh.Vertices[0].Position.X,curMesh.Vertices[0].Position.Y,curMesh.Vertices[0].Position.Z);
        glm::vec3 max(curMesh.Vertices[0].Position.X,curMesh.Vertices[0].Position.Y,curMesh.Vertices[0].Position.Z);

        std::cout<<"pmin x "<<min.x<<" y "<<min.y<<" z " <<min.z<<std::endl;
        std::cout<<"pmax x "<<max.x<<" y "<<max.y<<" z " <<max.z<<std::endl;

        for (int j = 0; j < curMesh.Vertices.size(); j++) {
            vbo.push_back(curMesh.Vertices[j].Position.X);
            vbo.push_back(curMesh.Vertices[j].Position.Y);
            vbo.push_back(curMesh.Vertices[j].Position.Z);
            vbo.push_back(curMesh.Vertices[j].Normal.X);
            vbo.push_back(curMesh.Vertices[j].Normal.Y);
            vbo.push_back(curMesh.Vertices[j].Normal.Z);
            vbo.push_back(curMesh.Vertices[j].TextureCoordinate.X);
            vbo.push_back(1.0f - curMesh.Vertices[j].TextureCoordinate.Y);

            glm::vec3 act(curMesh.Vertices[j].Position.X,curMesh.Vertices[j].Position.Y,curMesh.Vertices[j].Position.Z);

            //std::cout<<"min x "<<act.x<<" y "<<act.y<<" z " <<act.z<<std::endl;
            
            if((act.x <= min.x) && (act.y <= min.y) && (act.z <= min.z)){
                min = act;

                std::cout<<"asier1"<<std::endl;
            }

            if((act.x >= max.x) && (act.y >= max.y) && (act.z >= max.z)){
                max = act;

                std::cout<<"asier2"<<std::endl;
            }
        }
        
        std::cout<<"min x "<<min.x<<" y "<<min.y<<" z " <<min.z<<std::endl;
        std::cout<<"max x "<<max.x<<" y "<<max.y<<" z " <<max.z<<std::endl;

        // Calculate the size necessary for the object and the center of the object
        glm::vec3 size(max.x - min.x, max.y - min.y, max.z - min.z);
        glm::vec3 center((min.x + max.x)/2, (min.y + max.y)/2, (min.z + max.z)/2);
        glm::mat4 transform = glm::translate(glm::mat4(1), center) * glm::scale(glm::mat4(1), size);

        
        tempMesh.boundingBox.min = min;
        tempMesh.boundingBox.max = max;
        tempMesh.boundingBox.size = size;
        tempMesh.boundingBox.center = center;
        //tempMesh.boundingBox.transform = transform;
        
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