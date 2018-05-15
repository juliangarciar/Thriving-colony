#ifndef OBDMATERIAL_H
#define OBDMATERIAL_H

#include "OBDTypes.h"
#include "OBDEnums.h"

#include "OBDColor.h"

#include "Graphics/TTexture.h"
#include "ResourceManager/ResourceMTL.h"

class OBDMaterial {
	public:
		OBDMaterial();
		OBDMaterial(ResourceMTL*, std::string);
		~OBDMaterial();

        /**
         * @brief 
         * @param r 
         * @param sync 
         */
        void loadTextures(ResourceMTL *m, ResourceManager*, bool);

		void setMaterialName(std::string);

		void setAmbientColor(OBDColor);
		void setDiffuseColor(OBDColor);
		void setSpecularColor(OBDColor);
		void setSpecularShininess(i32);

		void setTexture(OBDEnums::TextureTypes, TTexture *);

		std::string getMaterialName();

		OBDColor getAmbientColor();
		OBDColor getDiffuseColor();
		OBDColor getSpecularColor();
		i32 getSpecularShininess();

		TTexture *getTexture(OBDEnums::TextureTypes);

		glslMaterial *getGLSLMaterial();
		glslTexture *getGLSLActiveTextures();
	private:
		std::string name;

        glslMaterial *material;
		glslTexture *activeTextures;

		TTexture* diffuseTextureMap;
		TTexture* ambientOclusionsTextureMap;
		TTexture* specularTextureMap;
		TTexture* alphaTextureMap;
		TTexture* bumpMap;
};

#endif