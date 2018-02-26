#include "TMaterial.h"

TMaterial::TMaterial() {

}

TMaterial::~TMaterial() {

}

void TMaterial::setName(std::string newName){
    materialName = newName;
}
std::string TMaterial::getName(){
    return materialName;
}

void TMaterial::setAmbientColor(Vector3<f32> aC){
    ambientColor = aC;
}
Vector3<f32> TMaterial::getAmbientColor(){
    return ambientColor;
}   

void TMaterial::setDiffuseColor(Vector3<f32> dC){
    diffuseColor = dC;
}
Vector3<f32> TMaterial::getDiffuseColor(){
    return diffuseColor;
}

void TMaterial::setSpecularColor(Vector3<f32> sC){
    specularColor = sC;
}
Vector3<f32> TMaterial::getSpecularColor(){
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

void TMaterial::setAmbientTextureMap(std::string atm){
    ambientTextureMap = atm;
}
std::string TMaterial::getAmbientTextureMap(){
    return ambientTextureMap;
}

void TMaterial::setDiffuseTextureMap(std::string dtm){
    diffuseTextureMap = dtm;
}
std::string TMaterial::getDiffuseTextureMap(){
    return diffuseTextureMap;
}

void TMaterial::setSpecularTextureMap(std::string stm){
    specularTextureMap = stm;
}
std::string TMaterial::getSpecularTextureMap(){
    return specularTextureMap;
}

void TMaterial::setAlphaTextureMap(std::string atm){
    alphaTextureMap = atm;
}
std::string TMaterial::getAlphaTextureMap(){
    return alphaTextureMap;
}

void TMaterial::setBumpMap(std::string bm){
    bumpMap = bm;
}
std::string TMaterial::getBumpMap(){
    return bumpMap;
}