#include "TMesh.h"
#include <IOEngine/ResourceManager/ResourceOBJ.h>

TMesh::TMesh() : TEntity() {

}

TMesh::~TMesh() {

}

void TMesh::loadMesh(std::string path) {
    //ResourceOBJ *o = (ResourceOBJ*)IO::Instance()->getResourceManager()->getResource(path);
    //mesh = *o->getOBJMesh();
}

void TMesh::beginDraw() {

}

void TMesh::endDraw() {

}