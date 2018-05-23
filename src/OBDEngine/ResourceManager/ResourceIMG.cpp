#include "ResourceIMG.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

ResourceIMG::ResourceIMG() {
	glTextureSet = false;
}

ResourceIMG::~ResourceIMG() {

}

void ResourceIMG::load(const char *path) {
    resource = stbi_load(
        path,
        &width, &height, &channels,
        STBI_default
    );
    if (!resource) {
        std::cerr << "Error: no se pudo leer la imagen '" << path << "'." << std::endl;
        exit(0);
    } 
}

void ResourceIMG::release() {
    stbi_image_free(resource);
	resource = nullptr;
}

void ResourceIMG::setGLTexture(){
	if (!glTextureSet){
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		
		// Nice trilinear filtering ...
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// ... which requires mipmaps. Generate them automatically.
		glGenerateMipmap(GL_TEXTURE_2D);
		
		if (channels == 1)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R, width, height, 0, GL_R, GL_UNSIGNED_BYTE, resource);
		else if (channels == 2)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RG, GL_UNSIGNED_BYTE, resource);
		else if (channels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, resource);
		else if (channels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, resource);

		glBindTexture(GL_TEXTURE_2D, 0);

		glTextureSet = true;
	}
}

void ResourceIMG::setIdentifier(const char *i) {
    identifier = i;
}

const char *ResourceIMG::getIdentifier() {
    return identifier;
}

unsigned char *ResourceIMG::getResource() {
    return resource;
}

i32 ResourceIMG::getWidth() { 
    return width;
}

i32 ResourceIMG::getHeight() {
    return height;
}

i32 ResourceIMG::getChannels() {
    return channels;
}

GLuint ResourceIMG::getTextureID() {
    return textureID;
}