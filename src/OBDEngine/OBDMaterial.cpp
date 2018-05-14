#include "OBDMaterial.h"

OBDMaterial::OBDMaterial(){
	material = new glslMaterial();

	material->ambientColor = glm::vec4(1, 1, 1, 1);
	material->diffuseColor = glm::vec4(1, 1, 1, 1);
	material->specularColor = glm::vec4(1, 1, 1, 1);

	diffuseTextureMap = "";
	ambientOclusionsTextureMap = "";
	specularTextureMap = "";
	alphaTextureMap = "";
	bumpMap = "";
}

OBDMaterial::OBDMaterial(ResourceMTL *m, std::string n){
	std::map<std::string, ResourceMaterial*>::iterator it = m->getResource().find(n);
	if (it != m->getResource().end()){
		material = new glslMaterial();

		material->ambientColor = glm::vec4(it -> second -> ambientColor, 1);
		material->diffuseColor = glm::vec4(it -> second -> diffuseColor, 1);
		material->specularColor = glm::vec4(it -> second -> specularColor, 1);
		material->shininess = it -> second -> specularExponent;
		
		diffuseTextureMap = it -> second -> diffuseTextureMap;
		ambientOclusionsTextureMap = it -> second -> ambientOclusionsTextureMap;
		specularTextureMap = it -> second -> specularTextureMap;
		alphaTextureMap = it -> second -> alphaTextureMap;
		bumpMap = it -> second -> bumpMap;
	} else {
		std::cout << "No se ha podido encontrar el material " << n << ", se creará un material por defecto." << std::endl;

		material = new glslMaterial();

		material->ambientColor = glm::vec4(1, 1, 1, 1);
		material->diffuseColor = glm::vec4(1, 1, 1, 1);
		material->specularColor = glm::vec4(1, 1, 1, 1);

		diffuseTextureMap = "";
		ambientOclusionsTextureMap = "";
		specularTextureMap = "";
		alphaTextureMap = "";
		bumpMap = "";
	}
}

OBDMaterial::~OBDMaterial(){

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

void OBDMaterial::setTexture(OBDEnums::TextureTypes tt , std::string p){
	switch(tt){
		case OBDEnums::TextureTypes::TEXTURE_DIFFUSE:
			diffuseTextureMap = p;
		break;
		case OBDEnums::TextureTypes::TEXTURE_OCLUSIONS:
			ambientOclusionsTextureMap = p;
		break;
		case OBDEnums::TextureTypes::TEXTURE_SPECULAR:
			specularTextureMap = p;
		break;
		case OBDEnums::TextureTypes::TEXTURE_ALPHA:
			alphaTextureMap = p;
		break;
		case OBDEnums::TextureTypes::TEXTURE_BUMP:
			bumpMap = p;
		break;
		default: break;
	}
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

std::string OBDMaterial::getTexture(OBDEnums::TextureTypes tt){
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
			return "";
		break;
	}
}

glslMaterial *OBDMaterial::getGLSLMaterial(){
	return material;
}