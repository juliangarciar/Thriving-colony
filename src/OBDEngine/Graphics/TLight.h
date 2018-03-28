#ifndef TLIGHT_H
#define TLIGHT_H

#include "TEntity.h"
#include "../OBDColor.h"

class TLight : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TLight(OBDColor, f32, bool = true);

        /**
         * @brief 
         * 
         */
        ~TLight();

        /**
         * @brief 
         * 
         */
        void beginDraw();

        /**
         * @brief 
         * 
         */
        void endDraw();
        
        /**
         * @brief 
         * 
         * @param OBDColor 
         */
        void setAmbientComponent(OBDColor, f32);
        
        /**
         * @brief 
         * 
         * @param OBDColor 
         */
        void setDiffuseComponent(OBDColor, f32);
        
        /**
         * @brief 
         * 
         * @param OBDColor 
         */
        void setSpecularComponent(OBDColor, f32);

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
    private:
        OBDEnums::LightTypes lightType;

        glslLight components;

        bool active;
};

#endif