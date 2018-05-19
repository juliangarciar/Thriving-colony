#ifndef OBDMATERIAL_H
#define OBDMATERIAL_H

#include "OBDTypes.h"
#include "OBDEnums.h"

#include "OBDColor.h"
#include "OBDTexture.h"

#include "ResourceManager/ResourceMTL.h"

class OBDMaterial {
	public:
		OBDMaterial();
		OBDMaterial(ResourceMTL*, std::string);
		~OBDMaterial();

		void setMaterialName(std::string);

		void setAmbientColor(OBDColor);
		void setDiffuseColor(OBDColor);
		void setSpecularColor(OBDColor);
		void setSpecularShininess(i32);

		void setTexture(OBDTexture *);

		std::string getMaterialName();

		OBDColor getAmbientColor();
		OBDColor getDiffuseColor();
		OBDColor getSpecularColor();
		i32 getSpecularShininess();

		OBDTexture *getTexture(OBDEnums::TextureTypes);

		glslMaterial *getGLSLMaterial();
		glslTexture *getGLSLActiveTextures();
	private:
		std::string name;

        glslMaterial *material;
		glslTexture *activeTextures;

		//ToDo: almacenar OBDTexture
		OBDTexture* diffuseTextureMap;
		OBDTexture* ambientOclusionsTextureMap;
		OBDTexture* specularTextureMap;
		OBDTexture* alphaTextureMap;
		OBDTexture* bumpMap;
};

#endif