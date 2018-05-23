#include "OBDTexture.h"

OBDTexture::OBDTexture(OBDEnums::TextureTypes t, ResourceIMG* i) {
	type = t;
	img = i;
	img->setGLTexture();
}

OBDTexture::~OBDTexture() {
	//Se libera en el gestor
}

OBDEnums::TextureTypes OBDTexture::getType() {
	return type;
}

ResourceIMG *OBDTexture::getTexture() {
	return img;
}