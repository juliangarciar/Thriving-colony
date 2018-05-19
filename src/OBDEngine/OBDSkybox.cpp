#include "OBDSkybox.h"

#include "Graphics/TEntity.h"

OBDSkybox::OBDSkybox(OBDTexture* texture) {
    skyboxNode = new TNode(new TSkybox(texture->getTexture()));
}

OBDSkybox::~OBDSkybox() {
	delete skyboxNode;
	skyboxNode = nullptr;
}

void OBDSkybox::setTexture(TTexture* texture) {
    TSkybox* s = (TSkybox*) skyboxNode -> getEntity();
    s -> setTexture(texture);
}

TSkybox* OBDSkybox::getSkyboxEntity() {
    TSkybox* s = (TSkybox*) skyboxNode -> getEntity();
    return s;
}

TNode* OBDSkybox::getFirstNode() {
    return skyboxNode;
}