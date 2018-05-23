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
        std::cerr << "Error: no se pudo abrir el fichero " << path << std::endl;
        exit(0);
    }

    defaultMaterialPath = loader.pathToMaterial;

    for (i32 i = 0; i < loader.LoadedMeshes.size(); i++) {
        // Copy one of the loaded meshes to be our current mesh
        objl::Mesh curMesh = loader.LoadedMeshes[i];

        ResourceMesh *tempMesh = new ResourceMesh();

        std::vector<f32> *vbo = new std::vector<f32>();

        tempMesh->name = curMesh.MeshName;
        tempMesh->defaultMaterialName = curMesh.MeshMaterial.name;
		tempMesh->isSetup = false;

        vbo->reserve(curMesh.Vertices.size() * 8);

        // Min and max bounding box
        glm::vec3 min(curMesh.Vertices[0].Position.X,curMesh.Vertices[0].Position.Y,curMesh.Vertices[0].Position.Z);
        glm::vec3 max(curMesh.Vertices[0].Position.X,curMesh.Vertices[0].Position.Y,curMesh.Vertices[0].Position.Z);

        for (i32 j = 0; j < curMesh.Vertices.size(); j++) {
            vbo->push_back(curMesh.Vertices[j].Position.X);
            vbo->push_back(curMesh.Vertices[j].Position.Y);
            vbo->push_back(curMesh.Vertices[j].Position.Z);
            vbo->push_back(curMesh.Vertices[j].Normal.X);
            vbo->push_back(curMesh.Vertices[j].Normal.Y);
            vbo->push_back(curMesh.Vertices[j].Normal.Z);
            vbo->push_back(curMesh.Vertices[j].TextureCoordinate.X);
            vbo->push_back(1.0f - curMesh.Vertices[j].TextureCoordinate.Y);

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
        
        tempMesh->vbo = vbo;
        tempMesh->ibo = new std::vector<u32>(curMesh.Indices.begin(), curMesh.Indices.end());

        meshArray->insert(std::pair<std::string, ResourceMesh*>(curMesh.MeshName, tempMesh));
    }
}

void ResourceOBJ::release() {
    meshArray->clear();
}

void ResourceOBJ::setupMesh(ResourceMesh *mesh) {
	if (!mesh->isSetup){
		// create buffers/arrays
		glGenVertexArrays(1, &mesh->VAO);
		glGenBuffers(1, &mesh->VBO);
		glGenBuffers(1, &mesh->IBO);

		glBindVertexArray(mesh->VAO);

		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
		glBufferData(GL_ARRAY_BUFFER, mesh->vbo->size() * sizeof(f32), mesh -> vbo -> data(), GL_STATIC_DRAW);  

		// load data into index buffers
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh -> ibo -> size() * sizeof(u32), mesh -> ibo -> data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(f32), BUFFER_OFFSET(0));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(f32), BUFFER_OFFSET(3 * sizeof(f32)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (3 + 3 + 2) * sizeof(f32), BUFFER_OFFSET((3 + 3) * sizeof(f32)));

		glBindVertexArray(0);

		mesh->isSetup = true;
	}
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