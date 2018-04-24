#ifndef COLOR_H
#define COLOR_H

#include <irrlicht/irrlicht.h>
#include <Types.h>
#include <MathEngine/Vector3.h>

using namespace irr;

class Color {
    public:
        Color(i32 r, i32 g, i32 b, i32 a);
        ~Color();

        void setColor(i32 r, i32 g, i32 b, i32 a);

        video::SColor* getColor();
    private:
        video::SColor* color;
};

#endif