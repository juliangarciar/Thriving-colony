#include "OBDSkybox.h"

OBDSkybox::OBDSkybox(OBDSceneNode *parent, OBDShaderProgram *program, std::vector<ResourceIMG *> textures) {
	texture = new TCubemapTexture(textures);

    skyboxNode = new TNode(new TSkybox(program->getShaderProgram(), texture));

	parent -> addChild(skyboxNode);
}

OBDSkybox::~OBDSkybox() {
	delete skyboxNode;
	skyboxNode = nullptr;
	delete texture;
	texture = nullptr;
}

void OBDSkybox::setTexture(std::vector<ResourceIMG *> textures) {
    TSkybox* s = (TSkybox*) skyboxNode -> getEntity();
	delete texture;
	texture = new TCubemapTexture(textures);
    s -> setTexture(texture);
}