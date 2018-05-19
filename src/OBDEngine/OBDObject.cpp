#include "OBDObject.h"

OBDObject::OBDObject(OBDSceneNode* p, u32 id, ResourceOBJ *obj, ResourceMTL *mtl) : OBDEntity(p) {
	meshes = new std::map<std::string, OBDMesh*>();
	materials = new std::map<std::string, OBDMaterial*>();

    std::map<std::string, ResourceMesh*> *meshmap = obj->getResource();

    for (std::map<std::string, ResourceMesh*>::iterator it = meshmap->begin(); it != meshmap->end(); ++it) {
		glslMesh *tmp = new glslMesh();
		tmp->vbo = it->second->vbo;
		tmp->ibo = it->second->indices;

		OBDMaterial *tempMat = new OBDMaterial(mtl, it->second->defaultMaterialName);

        OBDMesh *tempMesh = new OBDMesh(tmp, tempMat);
		tempMesh->setMaterialName(it->second->defaultMaterialName);
		tempMesh->setBoundingBox(it->second->aabbMin, it->second->aabbMax);

        tempMesh->getFirstNode()->setParent(scaleNode);
        scaleNode->addChild(tempMesh->getFirstNode());

        meshes->insert(std::pair<std::string, OBDMesh*>(it->second->name, tempMesh));
        materials->insert(std::pair<std::string, OBDMaterial*>(it->second->defaultMaterialName, tempMat));
    }

	ID = id;

	parent = nullptr;
	if (ID) refreshBoundingBox();
	parent = p;

	if (ID) p -> insertBoundingBox(ID, boundingBox);
}

OBDObject::~OBDObject(){
    for (std::map<std::string, OBDMesh*>::iterator it = meshes->begin(); it != meshes->end(); ++it) {
        delete it->second;
    }
    meshes->clear();

	delete meshes;
	meshes = nullptr;

    for (std::map<std::string, OBDMaterial*>::iterator it = materials->begin(); it != materials->end(); ++it) {
        delete it->second;
    }
    materials->clear();

	delete materials;
	materials = nullptr;
	
	if (parent != nullptr && ID) parent -> removeBoundingBox(ID);
}

void OBDObject::refreshBoundingBox(){
	if (ID){
		meshes->begin()->second->refreshBoundingBox();
		aabb::AABB matrix = meshes->begin()->second->getBoundingBox();
		for (std::map<std::string, OBDMesh*>::iterator i = meshes->begin(); i != meshes->end(); ++i) {
			i->second->refreshBoundingBox();
			matrix.merge(matrix, i->second->getBoundingBox());
		}
		boundingBox = matrix;

		if (parent != nullptr){
			parent -> refreshBoundingBox(ID, boundingBox);
		}
	}
}

void OBDObject::refreshModelMatrix(glm::mat4 parent){
	OBDEntity::refreshModelMatrix(parent);
    for (std::map<std::string, OBDMesh*>::iterator i = meshes->begin(); i != meshes->end(); ++i) {
		i->second->refreshModelMatrix(model_matrix);
	}
}

void OBDObject::setMaterial(std::string s, OBDMaterial *mtl){
	std::map<std::string, OBDMesh*>::iterator it = meshes->find(s);
	if (it != meshes->end()){
		it->second->setMaterial(mtl);
		materials->at(it->second->getMaterialName()) = mtl;
	}
}

void OBDObject::setMaterials(ResourceMTL *mtl) {
	//Delete previous materials
    for (std::map<std::string, OBDMaterial*>::iterator i = materials->begin(); i != materials->end(); ++i) {
		delete i->second;
	}
	meshes->clear();

	//Create new materials
    for (std::map<std::string, OBDMesh*>::iterator it = meshes->begin(); it != meshes->end(); ++it) {
		OBDMaterial *tempMat = new OBDMaterial(mtl, it->second->getMaterialName());
        it->second->setMaterial(tempMat);
        materials->insert(std::pair<std::string, OBDMaterial*>(it->first, tempMat));
    }
}

OBDMesh *OBDObject::getMesh(std::string meshName){
	std::map<std::string, OBDMesh*>::iterator i = meshes->find(meshName);
	if (i != meshes->end()) return i->second;
    else return nullptr;
}

std::map<std::string, OBDMesh*> *OBDObject::getMeshes(){
    return meshes;
}

u32 OBDObject::getMeshAmount(){
    return meshes->size();
}

OBDMaterial *OBDObject::getMaterial(std::string meshName){
	std::map<std::string, OBDMaterial*>::iterator i = materials->find(meshName);
	if (i != materials->end()) return i->second;
    else return nullptr;
}

std::map<std::string, OBDMaterial*> *OBDObject::getMaterials(){
    return materials;
}

aabb::AABB OBDObject::getBoundingBox(){
	return boundingBox;
}

u32 OBDObject::getID() {
	return ID;
}