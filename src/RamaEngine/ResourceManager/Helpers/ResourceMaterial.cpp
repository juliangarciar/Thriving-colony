#include "ResourceMaterial.h"

ResourceMaterial::ResourceMaterial() {

}

ResourceMaterial::~ResourceMaterial() {

}

void ResourceMaterial::setName(std::string newName){
    materialName = newName;
}
std::string ResourceMaterial::getName(){
    return materialName;
}

void ResourceMaterial::setAmbientColor(glm::vec3 aC){
    ambientColor = aC;
}
glm::vec3 ResourceMaterial::getAmbientColor(){
    return ambientColor;
}   

void ResourceMaterial::setDiffuseColor(glm::vec3 dC){
    diffuseColor = dC;
}
glm::vec3 ResourceMaterial::getDiffuseColor(){
    return diffuseColor;
}

void ResourceMaterial::setSpecularColor(glm::vec3 sC){
    specularColor = sC;
}
glm::vec3 ResourceMaterial::getSpecularColor(){
    return specularColor;
}

void ResourceMaterial::setSpecularExponent(f32 sE){
    specularExponent = sE;
}
f32 ResourceMaterial::getSpecularExponent(){
    return specularExponent;
}

void ResourceMaterial::setOpticalDensity(f32 oD){
    opticalDensity = oD;
}
f32 ResourceMaterial::getOpticalDensity(){
    return opticalDensity;
}

void ResourceMaterial::setDissolve(f32 d){
    dissolve = d;
}
f32 ResourceMaterial::getDissolve(){
    return dissolve;
}

void ResourceMaterial::setIllumination(i32 i){
    illumination = i;
}
i32 ResourceMaterial::getIllumination(){
    return illumination;
}

void ResourceMaterial::setAmbientTextureMap(std::string t){
    ambientTextureMap = t;
}
std::string ResourceMaterial::getAmbientTextureMap(){
    return ambientTextureMap;
}

void ResourceMaterial::setDiffuseTextureMap(std::string t){
    diffuseTextureMap = t;
}
std::string ResourceMaterial::getDiffuseTextureMap(){
    return diffuseTextureMap;
}

void ResourceMaterial::setSpecularTextureMap(std::string t){
    specularTextureMap = t;
}
std::string ResourceMaterial::getSpecularTextureMap(){
    return specularTextureMap;
}

void ResourceMaterial::setAlphaTextureMap(std::string t){
    alphaTextureMap = t;
}

std::string ResourceMaterial::getAlphaTextureMap(){
    return alphaTextureMap;
}

void ResourceMaterial::setBumpMap(std::string t){
    bumpMap = t;
}
std::string ResourceMaterial::getBumpMap(){
    return bumpMap;
}