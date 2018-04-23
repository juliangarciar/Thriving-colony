#include "OBDObject.h"

OBDObject::OBDObject(ResourceOBJ *obj, ResourceMTL *mtl) {
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);

    std::map<std::string, ResourceMesh> meshmap = obj->getResource();
    std::map<std::string, ResourceMaterial> matmap = mtl->getResource();

    for (std::map<std::string, ResourceMesh>::iterator it = meshmap.begin(); it != meshmap.end(); ++it) {
        std::map<std::string, ResourceMaterial>::iterator it2;
        it2 = matmap.find(it->second.defaultMaterialName);
        if (it2 == matmap.end()){
            std::cout << "No existe material " << it->second.defaultMaterialName << " para el mesh " << it->first << std::endl;
            exit(0);
        }

        OBDMesh *tempMesh = new OBDMesh(it->second, it2->second);
        tempMesh->getFirstNode()->setParent(scaleNode);
        scaleNode->addChild(tempMesh->getFirstNode());

        meshes.insert(std::pair<std::string, OBDMesh*>(it->second.name, tempMesh));
    }

}

OBDObject::OBDObject(OBDSceneNode* parent, ResourceOBJ *obj, ResourceMTL *mtl) {
    rotationNode = new TNode(new TTransform());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);

    parent->addChild(this);

    std::map<std::string, ResourceMesh> meshmap = obj->getResource();
    std::map<std::string, ResourceMaterial> matmap = mtl->getResource();

    for (std::map<std::string, ResourceMesh>::iterator it = meshmap.begin(); it != meshmap.end(); ++it) {
        std::map<std::string, ResourceMaterial>::iterator it2;
        it2 = matmap.find(it->second.defaultMaterialName);
        if (it2 == matmap.end()){
            std::cout << "No existe material " << it->second.defaultMaterialName << " para el mesh " << it->first << std::endl;
            exit(0);
        }

        OBDMesh *tempMesh = new OBDMesh(it->second, it2->second);
        tempMesh->getFirstNode()->setParent(scaleNode);
        scaleNode->addChild(tempMesh->getFirstNode());

        meshes.insert(std::pair<std::string, OBDMesh*>(it->second.name, tempMesh));
    }
}

OBDObject::~OBDObject(){
    for (std::map<std::string, OBDMesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it) {
        delete it->second;
    }
    meshes.clear();
    delete rotationNode;
    rotationNode = nullptr;
}

void OBDObject::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
    node_position += glm::vec3(tX, tY, tZ);
}

void OBDObject::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
    node_rotation += glm::vec3(rX, rY, rZ);
}

void OBDObject::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
    node_scale += glm::vec3(sX, sY, sZ);
}

void OBDObject::setPosition(glm::vec3 p) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    glm::vec3 o = node_position - p;
    t -> translate(o.x, o.y, o.z);
    node_position = p;
}

void OBDObject::setRotation(glm::vec3 r, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    glm::vec3 o = node_rotation - r;
    t -> rotate(o.x, o.y, o.z, angle);
    node_rotation = r;
}

void OBDObject::setScale(glm::vec3 s) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    glm::vec3 o = node_scale - s;
    t -> scale(o.x, o.y, o.z);
    node_scale = s;
}

void OBDObject::setActive(bool a) {
    rotationNode -> setActive(a);
}

bool OBDObject::getActive() {
    return rotationNode -> getActive();
}

void OBDObject::setMaterial(ResourceMTL *mtl) {
    std::map<std::string, ResourceMaterial> matmap = mtl->getResource();
    
    for (std::map<std::string, OBDMesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it) {
        if (matmap.find(it->second->getMaterialName()) != matmap.end()){
            it->second->setMaterial(matmap[it->second->getMaterialName()]);
        }
    }
}

void OBDObject::loadTextures(ResourceManager *r, bool sync){
    for (std::map<std::string, OBDMesh*>::iterator it = meshes.begin(); it != meshes.end(); ++it) {
        it->second->loadTextures(r, sync);
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

TNode *OBDObject::getFirstNode(){
    return rotationNode;
}