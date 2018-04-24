#include "Color.h"

using namespace irr;

Color::Color(i32 r, i32 g, i32 b, i32 a) {
    color = new video::SColor(a, r, g, b);
}

Color::~Color(){
    delete color;
}


void Color::setColor(i32 r, i32 g, i32 b, i32 a) {
    color -> setRed(r);
    color -> setGreen(g);
    color -> setBlue(b);
    color -> setAlpha(a);
}

video::SColor* Color::getColor() {
    return color;
}