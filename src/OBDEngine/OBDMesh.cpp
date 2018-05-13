#include "OBDMesh.h"

OBDMesh::OBDMesh(u32 id, ResourceMesh m, ResourceMaterial mat) : OBDEntity() {
    meshNode = new TNode(new TMesh(m, mat), scaleNode);

    mesh = m;
    material = mat;
	ID = id;
    name = m.name;
    materialName = m.defaultMaterialName;

	refreshModelMatrix(parent_model_matrix);
	refreshBoundingBox();
}

OBDMesh::OBDMesh(OBDSceneNode* p, u32 id, ResourceMesh m, ResourceMaterial mat) : OBDEntity(parent) {
    meshNode = new TNode(new TMesh(m, mat), scaleNode);

    mesh = m;
    material = mat;
	ID = id;
    name = m.name;
    materialName = m.defaultMaterialName;

	refreshModelMatrix(parent_model_matrix);
	refreshBoundingBox();

	p -> insertBoundingBox(ID, boundingBox);
}

OBDMesh::~OBDMesh() {
    delete rotationNode;
    rotationNode = nullptr;
	
	if (parent != nullptr) parent -> removeBoundingBox(ID);
}

void OBDMesh::loadTextures(ResourceManager *r, bool sync){
    TMesh* m = (TMesh*) meshNode -> getEntity();
    if (material.diffuseTextureMap != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material.diffuseTextureMap, sync);
        m -> setTexture(OBDEnums::TextureTypes::TEXTURE_DIFFUSE, new TTexture(tmp));
    }
    if (material.ambientOclusionsTextureMap != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material.ambientOclusionsTextureMap, sync);
        m -> setTexture(OBDEnums::TextureTypes::TEXTURE_OCLUSIONS, new TTexture(tmp));
    }
    if (material.specularTextureMap != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material.specularTextureMap, sync);
        m -> setTexture(OBDEnums::TextureTypes::TEXTURE_SPECULAR, new TTexture(tmp));
    }
    if (material.alphaTextureMap != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material.alphaTextureMap, sync);
        m -> setTexture(OBDEnums::TextureTypes::TEXTURE_ALPHA, new TTexture(tmp));
    }
    if (material.bumpMap != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material.bumpMap, sync);
        m -> setTexture(OBDEnums::TextureTypes::TEXTURE_BUMP, new TTexture(tmp));
    }
}

void OBDMesh::refreshBoundingBox(){
    TMesh* m = (TMesh*) meshNode -> getEntity();
	glm::vec4 mmin = model_matrix * glm::vec4(mesh.aabbMin, 1);
	glm::vec4 mmax = model_matrix * glm::vec4(mesh.aabbMax, 1);

	glm::vec3 min(mmin);
	glm::vec3 max(mmax);
	
	boundingBox = aabb::AABB(min, max);

	if (parent != nullptr){
		parent -> refreshBoundingBox(ID, boundingBox);
	}
}

void OBDMesh::setName(std::string a) {
	name = a;
}

void OBDMesh::setMaterial(ResourceMaterial mat){
    TMesh* m = (TMesh*) meshNode -> getEntity();
    m->setMaterial(mat);
}

void OBDMesh::setTexture(OBDTexture* t){
    TMesh* m = (TMesh*) meshNode -> getEntity();
    m -> setTexture(t->getType(), t->getTexture());
}

void OBDMesh::setMaterialName(std::string n) {
	name = n;
}

std::string OBDMesh::getName() {
    return name;
}

u32 OBDMesh::getID() {
	return ID;
}

std::string OBDMesh::getMaterialName() {
	return materialName;
}

TMesh* OBDMesh::getMeshEntity() {
    return (TMesh*) meshNode -> getEntity();
}

aabb::AABB OBDMesh::getBoundingBox(){
	return boundingBox;
}