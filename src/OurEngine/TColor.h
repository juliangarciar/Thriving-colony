#ifndef TCOLOR_H
#define TCOLOR_H

#include <Types.h>

class TColor {
    public:
        /**
         * @brief 
         * 
         */
        TColor();

        /**
         * @brief 
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        TColor(i32 red, i32 green, i32 blue, i32 alpha);

        /**
         * @brief 
         * 
         */
        ~TColor();


        /**
         * @brief 
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        void set(i32 red, i32 green, i32 blue, i32 alpha);
    private:
        i32 r, g, b, a;
};

#endif