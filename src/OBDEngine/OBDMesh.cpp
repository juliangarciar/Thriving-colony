#include "OBDMesh.h"

OBDMesh::OBDMesh(glslMesh *m, OBDMaterial *mat) : OBDEntity() {
	mesh = m;
	material = mat;

	aabbMin = glm::vec4(0,0,0,1);
	aabbMax = glm::vec4(1,1,1,1);

    meshNode = new TNode(new TMesh(mesh, material->getGLSLMaterial()), scaleNode);
}

OBDMesh::~OBDMesh() {
    delete rotationNode;
    rotationNode = nullptr;
}

void OBDMesh::loadTextures(ResourceManager *r, bool sync){
    TMesh* m = (TMesh*) meshNode -> getEntity();
    if (material->getTexture(OBDEnums::TextureTypes::TEXTURE_DIFFUSE) != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material->getTexture(OBDEnums::TextureTypes::TEXTURE_DIFFUSE), sync);
        m -> setTexture(OBDEnums::TextureTypes::TEXTURE_DIFFUSE, new TTexture(tmp));
    }
    if (material->getTexture(OBDEnums::TextureTypes::TEXTURE_OCLUSIONS) != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material->getTexture(OBDEnums::TextureTypes::TEXTURE_OCLUSIONS), sync);
        m -> setTexture(OBDEnums::TextureTypes::TEXTURE_OCLUSIONS, new TTexture(tmp));
    }
    if (material->getTexture(OBDEnums::TextureTypes::TEXTURE_SPECULAR) != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material->getTexture(OBDEnums::TextureTypes::TEXTURE_SPECULAR), sync);
        m -> setTexture(OBDEnums::TextureTypes::TEXTURE_SPECULAR, new TTexture(tmp));
    }
    if (material->getTexture(OBDEnums::TextureTypes::TEXTURE_ALPHA) != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material->getTexture(OBDEnums::TextureTypes::TEXTURE_ALPHA), sync);
        m -> setTexture(OBDEnums::TextureTypes::TEXTURE_ALPHA, new TTexture(tmp));
    }
    if (material->getTexture(OBDEnums::TextureTypes::TEXTURE_BUMP) != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material->getTexture(OBDEnums::TextureTypes::TEXTURE_BUMP), sync);
        m -> setTexture(OBDEnums::TextureTypes::TEXTURE_BUMP, new TTexture(tmp));
    }
}

void OBDMesh::refreshBoundingBox(){
	glm::vec4 mmin = model_matrix * aabbMin;
	glm::vec4 mmax = model_matrix * aabbMax;

	glm::vec3 min(mmin);
	glm::vec3 max(mmax);
	
	boundingBox = aabb::AABB(min, max);
}

void OBDMesh::setBoundingBox(glm::vec3 min, glm::vec3 max){
	aabbMin = glm::vec4(min, 1);
	aabbMax = glm::vec4(max, 1);
}

void OBDMesh::setMaterialName(std::string n) {
	materialName = n;
}

void OBDMesh::setMaterial(OBDMaterial *mat){
    TMesh* m = (TMesh*) meshNode -> getEntity();
	material = mat;
    m->setMaterial(mat->getGLSLMaterial());
}

void OBDMesh::setTexture(OBDTexture* t){
    TMesh* m = (TMesh*) meshNode -> getEntity();
    m -> setTexture(t->getType(), t->getTexture());
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