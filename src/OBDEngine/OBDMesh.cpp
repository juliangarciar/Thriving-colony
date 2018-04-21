#include "OBDMesh.h"

OBDMesh::OBDMesh(ResourceMesh m, ResourceMaterial mat){
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

void OBDMesh::setTexture(OBDEnums::TextureTypes tt, ResourceIMG *t){
    TMesh* m = (TMesh*) meshNode -> getEntity();
    m -> setTexture(tt, new TTexture(t));
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
    if (material.ambientTextureMap != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material.ambientTextureMap, sync);
        setTexture(OBDEnums::TextureTypes::TEXTURE_AMBIENT, tmp);
    }
    if (material.diffuseTextureMap != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material.diffuseTextureMap, sync);
        setTexture(OBDEnums::TextureTypes::TEXTURE_DIFFUSE, tmp);
    }
    if (material.specularTextureMap != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material.specularTextureMap, sync);
        setTexture(OBDEnums::TextureTypes::TEXTURE_SPECULAR, tmp);
    }
    if (material.alphaTextureMap != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material.alphaTextureMap, sync);
        setTexture(OBDEnums::TextureTypes::TEXTURE_ALPHA, tmp);
    }
    if (material.bumpMap != ""){
        ResourceIMG *tmp = (ResourceIMG*)r->getResource(material.bumpMap, sync);
        setTexture(OBDEnums::TextureTypes::TEXTURE_BUMP, tmp);
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