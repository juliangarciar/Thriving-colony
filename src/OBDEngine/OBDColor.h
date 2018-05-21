#ifndef OBDCOLOR_H
#define OBDCOLOR_H

#include "OBDTypes.h"

class OBDColor {
    public:
        /**
         * @brief 
         * 
         */
        OBDColor();

        /**
         * @brief 
         * 
         * @param red 
         * @param green 
         * @param blue 
         */
        OBDColor(f32 red, f32 green, f32 blue);

        /**
         * @brief 
         * 
         * @param rgb 
         */
        OBDColor(glm::vec3);

        /**
         * @brief 
         * 
         * @param rgba 
         */
        OBDColor(glm::vec4);

        /**
         * @brief 
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        OBDColor(f32 red, f32 green, f32 blue, f32 alpha);

        /**
         * @brief 
         * 
         */
        ~OBDColor();


        /**
         * @brief 
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        void set(f32 red, f32 green, f32 blue, f32 alpha);

        /**
         * @brief 
         * 
         * @param rgba
         */
        void set(glm::vec4 rgba);

        /**
         * @brief 
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        void set(f32 red, f32 green, f32 blue);

        /**
         * @brief 
         * 
         * @param rgba
         */
        void set(glm::vec3 rgb);

        /**
         * @brief 
         * 
         * @return glm::vec3 
         */
        glm::vec3 getRGB();

        /**
         * @brief 
         * 
         * @return glm::vec4 
         */
        glm::vec4 getRGBA();

        //Data
        f32 r, g, b, a;
    private:
};

#endif