#include "REMesh.h"

REMesh::REMesh(RESceneNode* parent, ResourceOBJ *obj) {
    rotationNode = new TNode(new TTransform(), parent->getSceneNode());
    translationNode = new TNode(new TTransform(), rotationNode);
    scaleNode = new TNode(new TTransform(), translationNode);
    //ToDo: vector?
    std::vector<TResourceMesh *> submeshes = *obj->getResource();
    meshNode = new TNode(new TMesh(submeshes.at(0)), scaleNode);
}

REMesh::~REMesh() {

}

void REMesh::rotate(f32 rX, f32 rY, f32 rZ, f32 angle) {
    TTransform* t = (TTransform*) rotationNode -> getEntity();
    t -> rotate(rX, rY, rZ, angle);
}

void REMesh::scale(f32 sX, f32 sY, f32 sZ) {
    TTransform* t = (TTransform*) scaleNode -> getEntity();
    t -> scale(sX, sY, sZ);
}

void REMesh::translate(f32 tX, f32 tY, f32 tZ) {
    TTransform* t = (TTransform*) translationNode -> getEntity();
    t -> translate(tX, tY, tZ);
}