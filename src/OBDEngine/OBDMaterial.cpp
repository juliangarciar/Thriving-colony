#include "OBDMaterial.h"

OBDMaterial::OBDMaterial(){
	material = new glslMaterial();

	material->ambientColor = glm::vec4(1, 1, 1, 1);
	material->diffuseColor = glm::vec4(1, 1, 1, 1);
	material->specularColor = glm::vec4(1, 1, 1, 1);
	material->shininess = 90;

	activeTextures = new glslTexture();

	activeTextures->diffuseTexture = 0;
	activeTextures->oclusionsTexture = 0;
	activeTextures->specularTexture = 0;
	activeTextures->alphaTexture = 0;
	activeTextures->bumpTexture = 0;
}

OBDMaterial::OBDMaterial(ResourceMTL *m, std::string n){
	std::map<std::string, ResourceMaterial*>::iterator it = m->getResource()->find(n);
	if (it != m->getResource()->end()){
		material = new glslMaterial();

		material->ambientColor = glm::vec4(it -> second -> ambientColor, 1);
		material->diffuseColor = glm::vec4(it -> second -> diffuseColor, 1);
		material->specularColor = glm::vec4(it -> second -> specularColor, 1);
		material->shininess = it -> second -> specularExponent;

		activeTextures = new glslTexture();

		activeTextures->diffuseTexture = 0;
		activeTextures->oclusionsTexture = 0;
		activeTextures->specularTexture = 0;
		activeTextures->alphaTexture = 0;
		activeTextures->bumpTexture = 0;

		name = it->second->materialName;
	} else {
		std::cout << "No se ha podido encontrar el material " << n << ", se creará un material por defecto." << std::endl;

		material = new glslMaterial();

		material->ambientColor = glm::vec4(1, 1, 1, 1);
		material->diffuseColor = glm::vec4(1, 1, 1, 1);
		material->specularColor = glm::vec4(1, 1, 1, 1);
		material->shininess = 90;

		activeTextures = new glslTexture();

		activeTextures->diffuseTexture = 0;
		activeTextures->oclusionsTexture = 0;
		activeTextures->specularTexture = 0;
		activeTextures->alphaTexture = 0;
		activeTextures->bumpTexture = 0;
	}
}

OBDMaterial::~OBDMaterial(){

}

void OBDMaterial::setMaterialName(std::string n){
	name = n;
}

void OBDMaterial::setAmbientColor(OBDColor c){
	material->ambientColor = c.getRGBA();
}

void OBDMaterial::setDiffuseColor(OBDColor c){
	material->diffuseColor = c.getRGBA();
}

void OBDMaterial::setSpecularColor(OBDColor c){
	material->specularColor = c.getRGBA();
}

void OBDMaterial::setSpecularShininess(i32 i){
	material->shininess = i;
}

void OBDMaterial::setTexture(OBDTexture *p){
	switch(p->getType()){
		case OBDEnums::TextureTypes::TEXTURE_DIFFUSE:
			diffuseTextureMap = p->getTexture();
			activeTextures->diffuseTexture = 1;
		break;
		case OBDEnums::TextureTypes::TEXTURE_OCLUSIONS:
			ambientOclusionsTextureMap = p->getTexture();
			activeTextures->oclusionsTexture = 1;
		break;
		case OBDEnums::TextureTypes::TEXTURE_SPECULAR:
			specularTextureMap = p->getTexture();
			activeTextures->specularTexture = 1;
		break;
		case OBDEnums::TextureTypes::TEXTURE_ALPHA:
			alphaTextureMap = p->getTexture();
			activeTextures->alphaTexture = 1;
		break;
		case OBDEnums::TextureTypes::TEXTURE_BUMP:
			bumpMap = p->getTexture();
			activeTextures->bumpTexture = 1;
		break;
		default: break;
	}
}

std::string OBDMaterial::getMaterialName(){
	return name;
}

OBDColor OBDMaterial::getAmbientColor(){
	return OBDColor(material->ambientColor);
}

OBDColor OBDMaterial::getDiffuseColor(){
	return OBDColor(material->diffuseColor);
}

OBDColor OBDMaterial::getSpecularColor(){
	return OBDColor(material->specularColor);
}

i32 OBDMaterial::getSpecularShininess(){
	return material->shininess;
}

TTexture* OBDMaterial::getTexture(OBDEnums::TextureTypes tt){
	switch(tt){
		case OBDEnums::TextureTypes::TEXTURE_DIFFUSE:
			return diffuseTextureMap;
		break;
		case OBDEnums::TextureTypes::TEXTURE_OCLUSIONS:
			return ambientOclusionsTextureMap;
		break;
		case OBDEnums::TextureTypes::TEXTURE_SPECULAR:
			return specularTextureMap;
		break;
		case OBDEnums::TextureTypes::TEXTURE_ALPHA:
			return alphaTextureMap;
		break;
		case OBDEnums::TextureTypes::TEXTURE_BUMP:
			return bumpMap;
		break;
		default: 
			return nullptr;
		break;
	}
}

glslMaterial *OBDMaterial::getGLSLMaterial(){
	return material;
}

glslTexture *OBDMaterial::getGLSLActiveTextures(){
	return activeTextures;
}