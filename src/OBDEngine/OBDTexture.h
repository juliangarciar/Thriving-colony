#ifndef OBDTEXTURE_H
#define OBDTEXTURE_H

#include "OBDTypes.h"
#include "OBDEnums.h"

#include "ResourceManager/ResourceIMG.h"

class OBDTexture {
	public:
		/**
		 * @brief Construct a new OBDTexture object
		 * 
		 */
		OBDTexture(OBDEnums::TextureTypes, ResourceIMG*);
		
		/**
		 * @brief Destroy the OBDTexture object
		 * 
		 */
		~OBDTexture();

		/**
		 * @brief Get the Type of the texture
		 * 
		 * @return OBDEnums::TextureTypes 
		 */
		OBDEnums::TextureTypes getType();

		/**
		 * @brief Get the Texture resource
		 * 
		 * @return ResourceIMG* 
		 */
		ResourceIMG *getTexture();
	private:
		OBDEnums::TextureTypes type;
		ResourceIMG *img;
};

#endif