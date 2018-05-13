#include "OBDSkybox.h"

#include "Graphics/TEntity.h"

OBDSkybox::OBDSkybox(TTexture* texture) {
    skyboxNode = new TNode(new TSkybox(texture));
}

OBDSkybox::~OBDSkybox() {

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