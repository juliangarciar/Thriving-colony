#ifndef TLIGHT_H
#define TLIGHT_H

#include "TEntity.h"
#include "TColor.h"

class TLight : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TLight();
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
         * @param TColor 
         */
        void setIntensity(TColor);
        /**
         * @brief 
         * 
         * @return TColor 
         */
        TColor getIntensity();

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
         */
        void setLightPosition(glm::vec3);

        /**
         * @brief returns the position of this light
         * 
         */
        glm::vec3 getPosition();
    private:
        glm::vec3 lightPosition;

        TColor intensity;

        bool active;
};

#endif