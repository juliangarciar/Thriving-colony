#include "TTexture.h"
#include "../ResourceManager/ResourceIMG.h"

TTexture::TTexture(ResourceIMG *t) {
	texture = t;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	
	// Nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap(GL_TEXTURE_2D);
	
	if (t->getChannels() == 1)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R, texture->getWidth(), texture->getHeight(), 0, GL_R, GL_UNSIGNED_BYTE, texture->getResource());
	else if (t->getChannels() == 2)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, texture->getWidth(), texture->getHeight(), 0, GL_RG, GL_UNSIGNED_BYTE, texture->getResource());
	else if (t->getChannels() == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->getWidth(), texture->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture->getResource());
	else if (t->getChannels() == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->getWidth(), texture->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->getResource());


    glBindTexture(GL_TEXTURE_2D, 0);
}

TTexture::~TTexture() {
	//El ResourceIMG no se libera aqui sino en el gestor de recursos
}

GLuint TTexture::getTextureID() {
    return textureID;
}

ResourceIMG *TTexture::getResourceIMG() {
	return texture;
}