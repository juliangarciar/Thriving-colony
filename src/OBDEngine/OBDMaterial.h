#ifndef OBDMATERIAL_H
#define OBDMATERIAL_H

#include "OBDTypes.h"
#include "OBDEnums.h"

#include "Graphics/TTexture.h"

class OBDTexture {
	public:
		OBDTexture(OBDEnums::TextureTypes, ResourceIMG*);
		~OBDTexture();

		OBDEnums::TextureTypes getType();
		TTexture *getTexture();
	private:
		OBDEnums::TextureTypes type;
		TTexture *tex;
};

#endif