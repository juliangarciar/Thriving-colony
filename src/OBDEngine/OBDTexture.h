#ifndef OBDTEXTURE_H
#define OBDTEXTURE_H

#include "OBDTypes.h"
#include "OBDEnums.h"

#include "ResourceManager/ResourceIMG.h"

class OBDTexture {
	public:
		OBDTexture(OBDEnums::TextureTypes, ResourceIMG*);
		~OBDTexture();

		OBDEnums::TextureTypes getType();
		ResourceIMG *getTexture();
	private:
		OBDEnums::TextureTypes type;
		ResourceIMG *img;
};

#endif