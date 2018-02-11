#ifndef TCOLOR_H
#define TCOLOR_H

#include <Types.h>

class TColor {
    public:
        TColor();
        TColor(i32 red, i32 green, i32 blue, i32 alpha);
        ~TColor();

        void set(i32 red, i32 green, i32 blue, i32 alpha);
    private:
        i32 r, g, b, a;
};

#endif