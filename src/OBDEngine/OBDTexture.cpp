#include "OBDTexture.h"

OBDTexture::OBDTexture(OBDEnums::TextureTypes t, ResourceIMG* i) {
	type = t;
	img = i;
	img->setGLTexture();
}

OBDTexture::~OBDTexture() {
	// To be freed up on the resource manager
}

OBDEnums::TextureTypes OBDTexture::getType() {
	return type;
}

ResourceIMG *OBDTexture::getTexture() {
	return img;
}