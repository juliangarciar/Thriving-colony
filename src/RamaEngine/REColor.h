#ifndef RECOLOR_H
#define RECOLOR_H

#include "RETypes.h"

class REColor {
    public:
        /**
         * @brief 
         * 
         */
        REColor();

        /**
         * @brief 
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        REColor(i32 red, i32 green, i32 blue, i32 alpha);

        /**
         * @brief 
         * 
         */
        ~REColor();


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