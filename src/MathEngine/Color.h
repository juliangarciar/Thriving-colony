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
        Color(i32 red, i32 green, i32 blue);

        /**
         * @brief 
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        Color(i32 red, i32 green, i32 blue, i32 alpha);

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
        void set(i32 red, i32 green, i32 blue);

        /**
         * @brief 
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        void set(i32 red, i32 green, i32 blue, i32 alpha);

        //Data
        u32 r, g, b, a;
    private:
};

#endif