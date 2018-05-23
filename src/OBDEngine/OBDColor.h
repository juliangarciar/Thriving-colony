#ifndef OBDCOLOR_H
#define OBDCOLOR_H

#include "OBDTypes.h"

class OBDColor {
    public:
        /**
         * @brief Construct a new OBDColor with default color black
         * 
         */
        OBDColor();

        /**
         * @brief Construct a new OBDColor
         * 
         * @param red 
         * @param green 
         * @param blue 
         */
        OBDColor(f32 red, f32 green, f32 blue);

        /**
         * @brief Construct a new OBDColor
         * 
         * @param rgb 
         */
        OBDColor(glm::vec3);

        /**
         * @brief Construct a new OBDColor
         * 
         * @param rgba 
         */
        OBDColor(glm::vec4);

        /**
         * @brief Construct a new OBDColor
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        OBDColor(f32 red, f32 green, f32 blue, f32 alpha);

        /**
         * @brief Destroy the OBDColor object
         * 
         */
        ~OBDColor();


        /**
         * @brief sets the color
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        void set(f32 red, f32 green, f32 blue, f32 alpha);

        /**
         * @brief sets the color
         * 
         * @param rgba
         */
        void set(glm::vec4 rgba);

        /**
         * @brief sets the color
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        void set(f32 red, f32 green, f32 blue);

        /**
         * @brief sets the color
         * 
         * @param rgba
         */
        void set(glm::vec3 rgb);

        /**
         * @brief returns the color
         * 
         * @return glm::vec3 
         */
        glm::vec3 getRGB();

        /**
         * @brief returns the color with the alpha value included
         * 
         * @return glm::vec4 
         */
        glm::vec4 getRGBA();

        //Data
        f32 r, g, b, a;
    private:
};

#endif