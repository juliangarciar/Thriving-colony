#ifndef TMATERIAL_H
#define TMATERIAL_H

#include <string>
#include "TColor.h"
#include <Types.h>
#include "../MathEngine/Vector3.h"

class TMaterial {
    public:
        TMaterial();
        ~TMaterial();

        void setName(std::string newName);
        std::string getName();

        void setAmbientColor(Vector3<f32> aC);
        Vector3<f32> getAmbientColor();

        void setDiffuseColor(Vector3<f32> dC);
        Vector3<f32> getDiffuseColor();

        void setSpecularColor(Vector3<f32> sC);
        Vector3<f32> getSpecularColor();

        void setSpecularExponent(f32 sE);
        f32 getSpecularExponent();

        void setOpticalDensity(f32 oD);
        f32 getOpticalDensity();

        void setDissolve(f32 d);
        f32 getDissolve();

        void setIllumination(i32 i);
        i32 getIllumination();

        void setAmbientTextureMap(std::string atm);
        std::string getAmbientTextureMap();

        void setDiffuseTextureMap(std::string dtm);
        std::string getDiffuseTextureMap();

        void setSpecularTextureMap(std::string stm);
        std::string getSpecularTextureMap();

        void setAlphaTextureMap(std::string atm);
        std::string getAlphaTextureMap();

        void setBumpMap(std::string bm);
        std::string getBumpMap();

    private:
        std::string materialName;
        Vector3<f32> ambientColor;
        Vector3<f32> diffuseColor;
        Vector3<f32> specularColor;
        f32 specularExponent;
        f32 opticalDensity;
        f32 dissolve;
        i32 illumination;
        std::string ambientTextureMap;
        std::string diffuseTextureMap;
        std::string specularTextureMap;
        std::string alphaTextureMap;
        std::string bumpMap;
};

#endif