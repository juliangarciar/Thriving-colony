#include "TMesh.h"

TMesh::TMesh() : TEntity() {

}

TMesh::~TMesh() {

}

void TMesh::loadMesh(std::string path) {
    IO::Instance()->getResourceManager()->getResource(path);
}

void TMesh::beginDraw() {

}

void TMesh::endDraw() {

}