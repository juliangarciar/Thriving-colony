#ifndef OBDMATERIAL_H
#define OBDMATERIAL_H

#include "OBDTypes.h"
#include "OBDEnums.h"

#include "OBDColor.h"
#include "OBDTexture.h"

#include "ResourceManager/ResourceMTL.h"

class OBDMaterial {
	public:
		/**
		 * @brief Construct a new OBDMaterial object
		 * 
		 */
		OBDMaterial();
		/**
		 * @brief Construct a new OBDMaterial object
		 * 
		 */
		OBDMaterial(ResourceMTL*, std::string);
		/**
		 * @brief Destroy the OBDMaterial object
		 * 
		 */
		~OBDMaterial();

		/**
		 * @brief Set the Material Name 
		 * 
		 */
		void setMaterialName(std::string);
		/**
		 * @brief Set the Ambient Color 
		 * 
		 */
		void setAmbientColor(OBDColor);
		/**
		 * @brief Set the Diffuse Color 
		 * 
		 */
		void setDiffuseColor(OBDColor);
		/**
		 * @brief Set the Specular Color 
		 * 
		 */
		void setSpecularColor(OBDColor);
		/**
		 * @brief Set the Specular Shininess 
		 * 
		 */
		void setSpecularShininess(i32);
		/**
		 * @brief Set the Texture 
		 * 
		 */
		void setTexture(OBDTexture *);
		/**
		 * @brief Get the Material Name 
		 * 
		 * @return std::string 
		 */
		std::string getMaterialName();
		/**
		 * @brief Get the Ambient Color 
		 * 
		 * @return OBDColor 
		 */
		OBDColor getAmbientColor();
		/**
		 * @brief Get the Diffuse Color 
		 * 
		 * @return OBDColor 
		 */
		OBDColor getDiffuseColor();
		/**
		 * @brief Get the Specular Color 
		 * 
		 * @return OBDColor 
		 */
		OBDColor getSpecularColor();
		/**
		 * @brief Get the Specular Shininess 
		 * 
		 * @return i32 
		 */
		i32 getSpecularShininess();
		/**
		 * @brief Get the Texture 
		 * 
		 * @return OBDTexture* 
		 */
		OBDTexture *getTexture(OBDEnums::TextureTypes);
		/**
		 * @brief return the material data used in shader
		 * 
		 * @return glslMaterial* 
		 */
		glslMaterial *getGLSLMaterial();
		/**
		 * @brief 
		 * 
		 * @return glslTexture* 
		 */
		glslTexture *getGLSLActiveTextures();
	private:
		std::string name;

        glslMaterial *material;
		glslTexture *activeTextures;

		OBDTexture* diffuseTextureMap;
		OBDTexture* ambientOclusionsTextureMap;
		OBDTexture* specularTextureMap;
		OBDTexture* alphaTextureMap;
};

#endif