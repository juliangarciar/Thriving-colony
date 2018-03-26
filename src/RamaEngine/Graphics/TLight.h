#ifndef TLIGHT_H
#define TLIGHT_H

#include "TEntity.h"
#include "../REColor.h"

class TLight : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TLight(REColor, f32, bool = true);

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
         * @param REColor 
         */
        void setAmbientComponent(REColor, f32);
        
        /**
         * @brief 
         * 
         * @param REColor 
         */
        void setDiffuseComponent(REColor, f32);
        
        /**
         * @brief 
         * 
         * @param REColor 
         */
        void setSpecularComponent(REColor, f32);

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
        REEnums::LightTypes lightType;

        Light components;

        bool active;
};

#endif