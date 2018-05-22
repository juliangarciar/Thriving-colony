#include "TCubemapTexture.h"
#include "../ResourceManager/ResourceIMG.h"

TCubemapTexture::TCubemapTexture(std::vector<ResourceIMG *> textures) {
	if (textures.size() != 6) {
		//std::cout << "Una textura de cubo debe tener 6 texturas" << std::endl;
		exit(0);
	}

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	
	// Nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  
	
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	for (int i = 0; i < textures.size(); i++){
		if (textures[i]->getChannels() == 1)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_R, textures[i]->getWidth(), textures[i]->getHeight(), 0, GL_R, GL_UNSIGNED_BYTE, textures[i]->getResource());
		else if (textures[i]->getChannels() == 2)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RG, textures[i]->getWidth(), textures[i]->getHeight(), 0, GL_RG, GL_UNSIGNED_BYTE, textures[i]->getResource());
		else if (textures[i]->getChannels() == 3)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, textures[i]->getWidth(), textures[i]->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, textures[i]->getResource());
		else if (textures[i]->getChannels() == 4)
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, textures[i]->getWidth(), textures[i]->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, textures[i]->getResource());
	}
	
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

TCubemapTexture::~TCubemapTexture() {
	//El ResourceIMG no se libera aqui sino en el gestor de recursos
}

GLuint TCubemapTexture::getTextureID() {
    return textureID;
}