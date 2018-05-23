#include "OBDImage.h"

OBDImage::OBDImage(OBDSceneNode* parent, OBDShaderProgram *s, ResourceIMG *i) {
	i->setGLTexture();
    imageNode = new TNode(new TImage(s->getShaderProgram(), i));

    parent->addChild(imageNode);
}

OBDImage::~OBDImage() {
    delete imageNode;
    imageNode = nullptr;
}

void OBDImage::setActive(bool active) {
    imageNode -> setActive(active);
}

bool OBDImage::getActive() {
    return imageNode -> getActive();
}

void OBDImage::setPosition(glm::vec3 p) {
    TImage* l = (TImage*) imageNode -> getEntity();
    l -> setPosition(p);
}

glm::vec3 OBDImage::getPosition() {
    TImage* l = (TImage*) imageNode -> getEntity();
    return l -> getPosition();
}