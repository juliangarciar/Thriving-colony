#ifndef OBDLIGHT_H
#define OBDLIGHT_H

#include "OBDEntity.h"
#include "OBDSceneNode.h"
#include "OBDColor.h"

#include "Graphics/TTransform.h"
#include "Graphics/TLight.h"

class OBDLight : public OBDEntity {
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
        OBDLight(OBDSceneNode* parent, OBDColor color, u32 intensity);

        /**
         * @brief 
         * 
         */
        ~OBDLight();

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
         * @return TLight* 
         */
        TLight* getLightEntity();

        /**
         * @brief Get the First Node object
         * 
         * @return TNode* 
         */
        TNode *getFirstNode();
    private:
        TNode* lightNode;

        OBDColor ambientColor;
        u32 ambientIntensity;
        OBDColor diffuseColor;
        u32 diffuseIntensity;
        OBDColor specularColor;
        u32 specularIntensity;
};

#endif