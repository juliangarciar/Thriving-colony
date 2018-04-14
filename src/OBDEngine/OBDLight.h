#ifndef OBDLIGHT_H
#define OBDLIGHT_H

#include "OBDTypes.h"
#include "OBDColor.h"
#include "Graphics/TNode.h"
#include "Graphics/TTransform.h"
#include "Graphics/TLight.h"

class OBDLight {
    public:
        /**
         * @brief 
         */
        OBDLight(OBDColor color, u32 intensity);

        /**
         * @brief 
         * 
         * @param parent 
         */
        OBDLight(TNode* parent, OBDColor color, u32 intensity);

        /**
         * @brief 
         * 
         */
        ~OBDLight();

        /**
         * @brief 
         * 
         * @param tX 
         * @param tY 
         * @param tZ 
         */
        void rotate(f32 rX, f32 rY, f32 rZ);

        /**
         * @brief 
         * 
         * @param sX 
         * @param sY 
         * @param sZ 
         */
        void scale(f32 sX, f32 sY, f32 sZ);

        /**
         * @brief 
         * 
         * @param tX 
         * @param tY 
         * @param tZ 
         */
        void translate(f32 tX, f32 tY, f32 tZ);

        /**
         * @brief 
         * 
         * @param OBDColor 
         */
        void setAmbientColor(OBDColor);

        /**
         * @brief 
         * 
         * @return OBDColor 
         */
        OBDColor getAmbientColor();
        
        /**
         * @brief 
         * 
         * @param OBDColor 
         */
        void setAmbientIntensity(u32);

        /**
         * @brief 
         * 
         * @return OBDColor 
         */
        u32 getAmbientIntensity();

        /**
         * @brief 
         * 
         * @param OBDColor 
         */
        void setDiffuseColor(OBDColor);

        /**
         * @brief 
         * 
         * @return OBDColor 
         */
        OBDColor getDiffuseColor();
        
        /**
         * @brief 
         * 
         * @param OBDColor 
         */
        void setDiffuseIntensity(u32);

        /**
         * @brief 
         * 
         * @return OBDColor 
         */
        u32 getDiffuseIntensity();

        /**
         * @brief 
         * 
         * @param OBDColor 
         */
        void setSpecularColor(OBDColor);

        /**
         * @brief 
         * 
         * @return OBDColor 
         */
        OBDColor getSpecularColor();
        
        /**
         * @brief 
         * 
         * @param OBDColor 
         */
        void setSpecularIntensity(u32);

        /**
         * @brief 
         * 
         * @return OBDColor 
         */
        u32 getSpecularIntensity();
        
        /**
         * @brief Set the Position object
         * 
         * @param p 
         */
        void setPosition(glm::vec3 p);

        /**
         * @brief Get the Position object
         * 
         * @return glm::vec3 
         */
        glm::vec3 getPosition();

        /**
         * @brief set the light to active or inactive
         * 
         * @param bool new light active state
         */
        void setActive(bool);

        /**
         * @brief returns wether or not the light is active
         * 
         * @return true if the light is active
         * @return false otherwise
         */
        bool getActive();
        
        /**
         * @brief 
         * 
         * @return TNode* 
         */
        TNode* getLightNode();
        
        /**
         * @brief 
         * 
         * @return TLight* 
         */
        TLight* getLightEntity();

        /**
         * @brief 
         * 
         */
        void setRotation(glm::vec3 r);

        /**
         * @brief 
         * 
         */
        void setScale(glm::vec3 s);

    private:
        TNode* lightNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;

        OBDColor ambientColor;
        u32 ambientIntensity;
        OBDColor diffuseColor;
        u32 diffuseIntensity;
        OBDColor specularColor;
        u32 specularIntensity;
};

#endif