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
        OBDColor(i32 red, i32 green, i32 blue);

        /**
         * @brief 
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        OBDColor(i32 red, i32 green, i32 blue, i32 alpha);

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
        void set(i32 red, i32 green, i32 blue, i32 alpha);

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
        void set(i32 red, i32 green, i32 blue);

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
        u32 r, g, b, a;
    private:
};

#endif