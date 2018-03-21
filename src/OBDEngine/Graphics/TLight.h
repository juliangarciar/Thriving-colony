#ifndef TLIGHT_H
#define TLIGHT_H

#include "TEntity.h"
#include "../OBDEColor.h"

class TLight : public TEntity {
    public:
        /**
         * @brief 
         * 
         */
        TLight(OBDEColor color, u32 intensity, bool = true);

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
         * @param OBDEColor 
         */
        void setColor(OBDEColor);

        /**
         * @brief 
         * 
         * @return OBDEColor 
         */
        OBDEColor getColor();

        /**
         * @brief 
         * 
         * @param OBDEColor 
         */
        void setIntensity(u32);

        /**
         * @brief 
         * 
         * @return OBDEColor 
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
    private:
        OBDEColor color;

        u32 intensity;

        glm::vec4 lightMatrix;

        bool active;
};

#endif