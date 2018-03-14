#include "TMaterial.h"

TMaterial::TMaterial() {
    ambientTextureMap = nullptr;
    diffuseTextureMap = nullptr;
    specularTextureMap = nullptr;
    alphaTextureMap = nullptr;
    bumpMap = nullptr;

}

TMaterial::~TMaterial() {

}

void TMaterial::setName(std::string newName){
    materialName = newName;
}
std::string TMaterial::getName(){
    return materialName;
}

void TMaterial::setAmbientColor(glm::vec3 aC){
    ambientColor = aC;
}
glm::vec3 TMaterial::getAmbientColor(){
    return ambientColor;
}   

void TMaterial::setDiffuseColor(glm::vec3 dC){
    diffuseColor = dC;
}
glm::vec3 TMaterial::getDiffuseColor(){
    return diffuseColor;
}

void TMaterial::setSpecularColor(glm::vec3 sC){
    specularColor = sC;
}
glm::vec3 TMaterial::getSpecularColor(){
    return specularColor;
}

void TMaterial::setSpecularExponent(f32 sE){
    specularExponent = sE;
}
f32 TMaterial::getSpecularExponent(){
    return specularExponent;
}

void TMaterial::setOpticalDensity(f32 oD){
    opticalDensity = oD;
}
f32 TMaterial::getOpticalDensity(){
    return opticalDensity;
}

void TMaterial::setDissolve(f32 d){
    dissolve = d;
}
f32 TMaterial::getDissolve(){
    return dissolve;
}

void TMaterial::setIllumination(i32 i){
    illumination = i;
}
i32 TMaterial::getIllumination(){
    return illumination;
}

void TMaterial::setAmbientTextureMap(std::string t, TTexture *atm){
    ambientTextureMap = atm;
}
TTexture *TMaterial::getAmbientTextureMap(){
    return ambientTextureMap;
}

void TMaterial::setDiffuseTextureMap(std::string t, TTexture *dtm){
    diffuseTextureMap = dtm;
}
TTexture *TMaterial::getDiffuseTextureMap(){
    return diffuseTextureMap;
}

void TMaterial::setSpecularTextureMap(std::string t, TTexture *stm){
    specularTextureMap = stm;
}
TTexture *TMaterial::getSpecularTextureMap(){
    return specularTextureMap;
}

void TMaterial::setAlphaTextureMap(std::string t, TTexture *atm){
    alphaTextureMap = atm;
}

TTexture *TMaterial::getAlphaTextureMap(){
    return alphaTextureMap;
}

void TMaterial::setBumpMap(std::string t, TTexture *bm){
    bumpMap = bm;
}
TTexture *TMaterial::getBumpMap(){
    return bumpMap;
}