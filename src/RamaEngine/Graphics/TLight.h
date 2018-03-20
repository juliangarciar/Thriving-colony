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
        TLight(REColor color, u32 intensity, bool = true);

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
        void setColor(REColor);

        /**
         * @brief 
         * 
         * @return REColor 
         */
        REColor getColor();

        /**
         * @brief 
         * 
         * @param REColor 
         */
        void setIntensity(u32);

        /**
         * @brief 
         * 
         * @return REColor 
         */
        u32 getIntensity();

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
        REColor color;

        u32 intensity;

        glm::vec4 lightMatrix;
        glm::vec3 lightPosition;
        bool active;
};

#endif