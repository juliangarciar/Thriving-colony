#include "Color.h"

Color::Color() {
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}

Color::Color(f32 red, f32 green, f32 blue) {
    r = red;
    g = green;
    b = blue;
    a = 1;
}

Color::Color(f32 red, f32 green, f32 blue, f32 alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

Color::~Color() {

}

void Color::set(f32 red, f32 green, f32 blue) {
    r = red;
    g = green;
    b = blue;
    a = 1;
}

void Color::set(f32 red, f32 green, f32 blue, f32 alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}