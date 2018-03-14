#ifndef TMATERIAL_H
#define TMATERIAL_H

#include "../RETypes.h"
#include "../REColor.h"
#include "TTexture.h"

class TMaterial {
    public:
        TMaterial();
        ~TMaterial();

        void setName(std::string newName);
        std::string getName();

        void setAmbientColor(glm::vec3 aC);
        glm::vec3 getAmbientColor();

        void setDiffuseColor(glm::vec3 dC);
        glm::vec3 getDiffuseColor();

        void setSpecularColor(glm::vec3 sC);
        glm::vec3 getSpecularColor();

        void setSpecularExponent(f32 sE);
        f32 getSpecularExponent();

        void setOpticalDensity(f32 oD);
        f32 getOpticalDensity();

        void setDissolve(f32 d);
        f32 getDissolve();

        void setIllumination(i32 i);
        i32 getIllumination();

        void setAmbientTextureMap(std::string, TTexture *atm);
        TTexture *getAmbientTextureMap();

        void setDiffuseTextureMap(std::string, TTexture *dtm);
        TTexture *getDiffuseTextureMap();

        void setSpecularTextureMap(std::string, TTexture *stm);
        TTexture *getSpecularTextureMap();

        void setAlphaTextureMap(std::string, TTexture *atm);
        TTexture *getAlphaTextureMap();

        void setBumpMap(std::string, TTexture *bm);
        TTexture *getBumpMap();

    private:
        std::string materialName;
        glm::vec3 ambientColor;
        glm::vec3 diffuseColor;
        glm::vec3 specularColor;
        
        f32 specularExponent;
        f32 opticalDensity;
        f32 dissolve;
        i32 illumination;

        TTexture *ambientTextureMap;
        TTexture *diffuseTextureMap;
        TTexture *specularTextureMap;
        TTexture *alphaTextureMap;
        TTexture *bumpMap;
};

#endif