#ifndef OBDTEXTURE_H
#define OBDTEXTURE_H

#include <GLFW/glfw3.h>
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