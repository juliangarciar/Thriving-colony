#include "TTexture.h"
#include "../ResourceManager/ResourceIMG.h"

TTexture::TTexture(ResourceIMG *t){
	texture = t;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->getWidth(), texture->getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, texture->getResource());

	// Nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap(GL_TEXTURE_2D);
}

TTexture::~TTexture(){

}

GLuint TTexture::getTextureID(){
    return textureID;
}

ResourceIMG *TTexture::getResourceIMG(){
	return texture;
}