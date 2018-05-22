#include "ResourceOBJ.h"

#include <objloader/OBJ_Loader.h>
#include <glm/glm.hpp>

ResourceOBJ::ResourceOBJ() {
	meshArray = new std::map<std::string, ResourceMesh*>();
}

ResourceOBJ::~ResourceOBJ() {
	for (std::map<std::string, ResourceMesh*>::iterator it = meshArray->begin(); it != meshArray->end(); ++it) {
		delete it->second;
	}
	meshArray->clear();
    delete meshArray;
	meshArray = nullptr;
}

void ResourceOBJ::load(const char *path) {
    setIdentifier(path);
    objl::Loader loader;
    
    bool loadout = loader.LoadFile(path);
    if (!loadout) {
        //std::cout << "Error al abrir el fichero " << path << std::endl;
        exit(0);
    }

    defaultMaterialPath = loader.pathToMaterial;

    for (i32 i = 0; i < loader.LoadedMeshes.size(); i++) {
        // Copy one of the loaded meshes to be our current mesh
        objl::Mesh curMesh = loader.LoadedMeshes[i];

        ResourceMesh *tempMesh = new ResourceMesh();

        std::vector<f32> vbo;

        vbo.reserve(curMesh.Vertices.size() * 8);

        // Min and max bounding box
        glm::vec3 min(curMesh.Vertices[0].Position.X,curMesh.Vertices[0].Position.Y,curMesh.Vertices[0].Position.Z);
        glm::vec3 max(curMesh.Vertices[0].Position.X,curMesh.Vertices[0].Position.Y,curMesh.Vertices[0].Position.Z);

        for (i32 j = 0; j < curMesh.Vertices.size(); j++) {
            vbo.push_back(curMesh.Vertices[j].Position.X);
            vbo.push_back(curMesh.Vertices[j].Position.Y);
            vbo.push_back(curMesh.Vertices[j].Position.Z);
            vbo.push_back(curMesh.Vertices[j].Normal.X);
            vbo.push_back(curMesh.Vertices[j].Normal.Y);
            vbo.push_back(curMesh.Vertices[j].Normal.Z);
            vbo.push_back(curMesh.Vertices[j].TextureCoordinate.X);
            vbo.push_back(1.0f - curMesh.Vertices[j].TextureCoordinate.Y);

            glm::vec3 act(curMesh.Vertices[j].Position.X,curMesh.Vertices[j].Position.Y,curMesh.Vertices[j].Position.Z);
            
            if (act.x <= min.x) {
				min.x = act.x;
			}

			if (act.y <= min.y) {
                min.y = act.y;
            }
			
			if (act.z <= min.z) {
				min.z = act.z;
			}

            if (act.x >= max.x) {
				max.x = act.x;
			}
			
			if (act.y >= max.y) {
				max.y = act.y;
			}

			if (act.z >= max.z) {
                max.z = act.z;
            }
        }

        tempMesh->aabbMin = min;
        tempMesh->aabbMax = max;
        
        tempMesh->name = curMesh.MeshName;
        tempMesh->vbo = vbo;
        tempMesh->indices = std::vector<u32>(curMesh.Indices.begin(), curMesh.Indices.end());
        tempMesh->defaultMaterialName = curMesh.MeshMaterial.name;

        meshArray->insert(std::pair<std::string, ResourceMesh*>(curMesh.MeshName, tempMesh));
    }
}

void ResourceOBJ::release() {
    meshArray->clear();
}

void ResourceOBJ::setIdentifier(const char *i) {
    identifier = i;
}

const char *ResourceOBJ::getIdentifier() {
    return identifier;
}

std::map<std::string, ResourceMesh*> *ResourceOBJ::getResource() {
    return meshArray;
}

std::string ResourceOBJ::getDefaultMaterialPath() {
    return defaultMaterialPath;
}