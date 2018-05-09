#include "OBDMesh.h"

OBDMesh::OBDMesh(ResourceMesh m, ResourceMaterial mat){
	node_position = glm::vec3(0);
	node_rotation = glm::vec3(0);
	node_scale = glm::vec3(0);

    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);

    meshNode = new TNode(new TMesh(m, mat), scaleNode);

    mesh = m;
    material = mat;
    name = m.name;
    materialName = m.defaultMaterialName;
}

OBDMesh::OBDMesh(OBDSceneNode* parent, ResourceMesh m, ResourceMaterial mat){
	node_position = glm::vec3(0);
	node_rotation = glm::vec3(0);
	node_scale = glm::vec3(0);
	
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);

    meshNode = new TNode(new TMesh(m, mat), scaleNode);

    mesh = m;
    material = mat;
    name = m.name;
    materialName = m.defaultMaterialName;

    parent->addChild(this);
}

OBDMesh::~OBDMesh() {
    delete rotationNode;
    rotationNode = nullptr;
}

void OBDMesh::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
    node_position += glm::vec3(tX, tY, tZ);
}

void OBDMesh::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
    node_rotation += glm::vec3(rX, rY, rZ);
}

void OBDMesh::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
    node_scale += glm::vec3(sX, sY, sZ);
}

void OBDMesh::setPosition(glm::vec3 p) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    glm::vec3 o = node_position - p;
    t -> translate(o.x, o.y, o.z);
    node_position = p;
}

void OBDMesh::setRotation(glm::vec3 r, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    glm::vec3 o = node_rotation - r;
    t -> rotate(o.x, o.y, o.z, angle);
    node_rotation = r;
}

void OBDMesh::setScale(glm::vec3 s) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    glm::vec3 o = node_scale - s;
    t -> scale(o.x, o.y, o.z);
    node_scale = s;
}

glm::vec3 OBDMesh::getPosition(){
	return node_position;
}

glm::vec3 OBDMesh::getRotation(){
	return node_rotation;
}

glm::vec3 OBDMesh::getScale(){
	return node_scale;
}

void OBDMesh::setActive(bool a) {
    meshNode -> setActive(a);
}

bool OBDMesh::getActive() {
    return meshNode -> getActive();
}

void OBDMesh::setMaterial(ResourceMaterial mat){
    TMesh* m = (TMesh*) meshNode -> getEntity();
    m->setMaterial(mat);
}

void OBDMesh::setTexture(OBDTexture* t){
    TMesh* m = (TMesh*) meshNode -> getEntity();
    m -> setTexture(t->getType(), t->getTexture());
}

void OBDMesh::setName(std::string n) {
	name = n;
}

std::string OBDMesh::getName() {
	return name;
}

void OBDMesh::setMaterialName(std::string n) {
	name = n;
}

std::string OBDMesh::getMaterialName() {
	return materialName;
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

void OBDMesh::setID(GLuint i) {
	ID = i;
}

GLuint OBDMesh::getID() {
	return ID;
}

TMesh* OBDMesh::getMeshEntity() {
    return (TMesh*) meshNode -> getEntity();
}

TNode *OBDMesh::getFirstNode(){
    return rotationNode;
}