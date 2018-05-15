#include "OBDMesh.h"

OBDMesh::OBDMesh(glslMesh *m, OBDMaterial *mat) : OBDEntity() {
	aabbMin = glm::vec4(0,0,0,1);
	aabbMax = glm::vec4(1,1,1,1);

    meshNode = new TNode(new TMesh(m, mat), scaleNode);
}

OBDMesh::~OBDMesh() {
	
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

void OBDMesh::setMaterial(OBDMaterial *mat){
    TMesh* m = (TMesh*) meshNode -> getEntity();
    m->setMaterial(mat);
}

void OBDMesh::setMaterialName(std::string n) {
	materialName = n;
}

OBDMaterial *OBDMesh::getMaterial() {
    TMesh* m = (TMesh*) meshNode -> getEntity();
	return m->getMaterial();
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