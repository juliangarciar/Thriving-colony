#include "OBDTexture.h"

OBDTexture::OBDTexture(OBDEnums::TextureTypes t, ResourceIMG* i){
	type = t;
	tex = new TTexture(i);
}

OBDTexture::~OBDTexture() {

}

OBDEnums::TextureTypes OBDTexture::getType(){
	return type;
}

TTexture *OBDTexture::getTexture(){
	return tex;
}