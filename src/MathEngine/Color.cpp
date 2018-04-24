#include "Color.h"

Color::Color(){
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}

Color::Color(i32 red, i32 green, i32 blue) {
    r = red;
    g = green;
    b = blue;
    a = 1.f;
}

Color::Color(i32 red, i32 green, i32 blue, i32 alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

Color::~Color() {

}

void Color::set(i32 red, i32 green, i32 blue){
    r = red;
    g = green;
    b = blue;
    a = 0;
}

void Color::set(i32 red, i32 green, i32 blue, i32 alpha){
    r = red;
    g = green;
    b = blue;
    a = alpha;
}