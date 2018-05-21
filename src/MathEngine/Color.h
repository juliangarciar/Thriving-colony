#ifndef COLOR_H
#define COLOR_H

#include <Types.h>

class Color {
    public:
        /**
         * @brief 
         * 
         */
        Color();

        /**
         * @brief 
         * 
         * @param red 
         * @param green 
         * @param blue 
         */
        Color(f32 red, f32 green, f32 blue);

        /**
         * @brief 
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        Color(f32 red, f32 green, f32 blue, f32 alpha);

        /**
         * @brief 
         * 
         */
        ~Color();

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
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        void set(f32 red, f32 green, f32 blue, f32 alpha);

        //Data
        f32 r, g, b, a;
    private:
};

#endif