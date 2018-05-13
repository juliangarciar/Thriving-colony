#include "OBDObject.h"

OBDObject::OBDObject(OBDSceneNode* p, u32 id, ResourceOBJ *obj, ResourceMTL *mtl) : OBDEntity(p) {
    std::map<std::string, ResourceMesh> meshmap = obj->getResource();
    std::map<std::string, ResourceMaterial> matmap = mtl->getResource();

    for (std::map<std::string, ResourceMesh>::iterator it = meshmap.begin(); it != meshmap.end(); ++it) {
        std::map<std::string, ResourceMaterial>::iterator it2;
        it2 = matmap.find(it->second.defaultMaterialName);

		ResourceMaterial mat;
        if (it2 != matmap.end()){
			mat = it2->second;
        } else {
			mat.ambientColor = glm::vec3(1, 1, 1);
            std::cout << "No existe material " << it->second.defaultMaterialName << " para el mesh " << it->first << ". Utilizando un material vacio" << std::endl;
		}

        OBDMesh *tempMesh = new OBDMesh(id, it->second, mat);
        tempMesh->getFirstNode()->setParent(scaleNode);
        scaleNode->addChild(tempMesh->getFirstNode());

        meshes.insert(std::pair<std::string, OBDMesh*>(it->second.name, tempMesh));
    }

	ID = id;

	parent = nullptr;
	refreshModelMatrix(parent_model_matrix);
	refreshBoundingBox();
	parent = p;

	p -> insertBoundingBox(ID, boundingBox);
}

OBDObject::~OBDObject(){
    for (std::map<std::string, OBDMesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it) {
        delete it->second;
    }

    meshes.clear();
	
	if (parent != nullptr) parent -> removeBoundingBox(ID);
}

void OBDObject::loadTextures(ResourceManager *r, bool sync){
    for (std::map<std::string, OBDMesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it) {
        it->second->loadTextures(r, sync);
    }
}

void OBDObject::refreshBoundingBox(){
	meshes.begin()->second->refreshBoundingBox();
	aabb::AABB matrix = meshes.begin()->second->getBoundingBox();
    for (std::map<std::string, OBDMesh*>::iterator i = meshes.begin(); i != meshes.end(); ++i) {
		i->second->refreshBoundingBox();
		matrix.merge(matrix, i->second->getBoundingBox());
	}
	boundingBox = matrix;

	if (parent != nullptr){
		parent -> refreshBoundingBox(ID, boundingBox);
	}
}

void OBDObject::refreshModelMatrix(glm::mat4 parent){
	OBDEntity::refreshModelMatrix(parent);
    for (std::map<std::string, OBDMesh*>::iterator i = meshes.begin(); i != meshes.end(); ++i) {
		i->second->refreshModelMatrix(model_matrix);
	}
}

void OBDObject::setMaterial(ResourceMTL *mtl) {
    std::map<std::string, ResourceMaterial> matmap = mtl->getResource();
    
    for (std::map<std::string, OBDMesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it) {
        if (matmap.find(it->second->getMaterialName()) != matmap.end()){
            it->second->setMaterial(matmap[it->second->getMaterialName()]);
        }
    }
}

u32 OBDObject::getMeshAmount(){
    return meshes.size();
}

OBDMesh *OBDObject::getMesh(std::string meshName){
    return meshes[meshName];
}

std::map<std::string, OBDMesh*> OBDObject::getMeshes(){
    return meshes;
}

aabb::AABB OBDObject::getBoundingBox(){
	return boundingBox;
}

u32 OBDObject::getID() {
	return ID;
}