#ifndef OBDMATERIAL_H
#define OBDMATERIAL_H

#include "OBDTypes.h"
#include "OBDEnums.h"

#include "OBDColor.h"

#include "ResourceManager/ResourceMTL.h"

class OBDMaterial {
	public:
		OBDMaterial();
		OBDMaterial(ResourceMTL*, std::string);
		~OBDMaterial();

		void setAmbientColor(OBDColor);
		void setDiffuseColor(OBDColor);
		void setSpecularColor(OBDColor);

		void setTexture(OBDEnums::TextureTypes, std::string);

		OBDColor getAmbientColor();
		OBDColor getDiffuseColor();
		OBDColor getSpecularColor();

		std::string getTexture(OBDEnums::TextureTypes);

		glslMaterial *getGLSLMaterial();
	private:
        glslMaterial *material;

		std::string diffuseTextureMap;
		std::string ambientOclusionsTextureMap;
		std::string specularTextureMap;
		std::string alphaTextureMap;
		std::string bumpMap;
};

#endif