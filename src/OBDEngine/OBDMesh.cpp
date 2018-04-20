#include "OBDMesh.h"

OBDMesh::OBDMesh(ResourceOBJ *obj, ResourceMTL *mtl) {
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);

    std::map<std::string, ResourceMesh *> submeshes = *obj->getResource();
    std::map<std::string, ResourceMaterial *> submats = *mtl->getResource();

    for (std::map<std::string, ResourceMesh *>::iterator it=submeshes.begin(); it!=submeshes.end(); ++it) {
        std::map<std::string, ResourceMaterial *>::iterator it2;
        it2 = submats.find(it->second->getDefaultMaterialName());
        if (it2 == submats.end()){
            std::cout << "No existe material " << it->second->getDefaultMaterialName() << " para el mesh " << it->first << std::endl;
            exit(0);
        }

        TMesh *tempMesh = new TMesh(it->second, it2->second);

        meshes.insert(std::pair<std::string, TMesh*>(it->second->getName(), tempMesh));
    }

    //ToDo: un nodo para cada submesh
    meshNode = new TNode(meshes.begin()->second, scaleNode);
}

OBDMesh::OBDMesh(OBDSceneNode* parent, ResourceOBJ *obj, ResourceMTL *mtl) {
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);

    parent->addChild(this);

    std::map<std::string, ResourceMesh *> submeshes = *obj->getResource();
    std::map<std::string, ResourceMaterial *> submats = *mtl->getResource();

    for (std::map<std::string, ResourceMesh *>::iterator it=submeshes.begin(); it!=submeshes.end(); ++it) {
        std::map<std::string, ResourceMaterial *>::iterator it2;
        it2 = submats.find(it->second->getDefaultMaterialName());
        if (it2 == submats.end()){
            std::cout << "No existe material " << it->second->getDefaultMaterialName() << " para el mesh " << it->first << std::endl;
            exit(0);
        }

        TMesh *tempMesh = new TMesh(it->second, it2->second);

        meshes.insert(std::pair<std::string, TMesh*>(it->second->getName(), tempMesh));
    }

    //ToDo: un nodo para cada submesh
    meshNode = new TNode(meshes.begin()->second, scaleNode);
}

OBDMesh::~OBDMesh() {

}

//ToDo: poder cambiar material de cada mesh (o de todos cambiando el MTL)

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

void OBDMesh::setTexture(std::string name, OBDEnums::TextureTypes tt, ResourceIMG *t){
    meshes[name] -> setTexture(tt, new TTexture(t));
}

u32 OBDMesh::getMeshAmount(){
    return meshes.size();
}

TMesh *OBDMesh::getShape(std::string meshName){
    return meshes[meshName];
}

std::map<std::string, TMesh*> OBDMesh::getMeshes(){
    return meshes;
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

void OBDMesh::setName(std::string n) {
    TMesh* m = (TMesh*) meshNode -> getEntity();
    m -> setName(n);
}

std::string OBDMesh::getName() {
    TMesh* m = (TMesh*) meshNode -> getEntity();
    return m -> getName();
}

void OBDMesh::setID(GLuint i) {
    TMesh* m = (TMesh*) meshNode -> getEntity();
    m -> setID(i);
}

GLuint OBDMesh::getID() {
    TMesh* m = (TMesh*) meshNode -> getEntity();
    return m -> getID();
}

TMesh* OBDMesh::getMeshEntity() {
    return (TMesh*) meshNode -> getEntity();
}

TNode *OBDMesh::getFirstNode(){
    return rotationNode;
}