#ifndef RELIGHT_H
#define RELIGHT_H

#include "RETypes.h"
#include "REColor.h"
#include "Graphics/TNode.h"
#include "Graphics/TTransform.h"
#include "Graphics/TLight.h"

class RELight {
    public:
        /**
         * @brief 
         */
        RELight(REColor color, u32 intensity);

        /**
         * @brief 
         * 
         * @param parent 
         */
        RELight(TNode* parent, REColor color, u32 intensity);

        /**
         * @brief 
         * 
         */
        ~RELight();

        /**
         * @brief 
         * 
         * @param tX 
         * @param tY 
         * @param tZ 
         */
        void rotate(f32 rX, f32 rY, f32 rZ, f32 angle);

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
         * @param REColor 
         */
        void setAmbientColor(REColor);

        /**
         * @brief 
         * 
         * @return REColor 
         */
        REColor getAmbientColor();
        
        /**
         * @brief 
         * 
         * @param REColor 
         */
        void setAmbientIntensity(u32);

        /**
         * @brief 
         * 
         * @return REColor 
         */
        u32 getAmbientIntensity();

        /**
         * @brief 
         * 
         * @param REColor 
         */
        void setDiffuseColor(REColor);

        /**
         * @brief 
         * 
         * @return REColor 
         */
        REColor getDiffuseColor();
        
        /**
         * @brief 
         * 
         * @param REColor 
         */
        void setDiffuseIntensity(u32);

        /**
         * @brief 
         * 
         * @return REColor 
         */
        u32 getDiffuseIntensity();

        /**
         * @brief 
         * 
         * @param REColor 
         */
        void setSpecularColor(REColor);

        /**
         * @brief 
         * 
         * @return REColor 
         */
        REColor getSpecularColor();
        
        /**
         * @brief 
         * 
         * @param REColor 
         */
        void setSpecularIntensity(u32);

        /**
         * @brief 
         * 
         * @return REColor 
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

    private:
        TNode* lightNode;
        TNode* rotationNode;
        TNode* translationNode;
        TNode* scaleNode;

        REColor ambientColor;
        u32 ambientIntensity;
        REColor diffuseColor;
        u32 diffuseIntensity;
        REColor specularColor;
        u32 specularIntensity;
};

#endif