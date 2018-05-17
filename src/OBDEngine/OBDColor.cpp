#include "OBDColor.h"

OBDColor::OBDColor(){
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}

OBDColor::OBDColor(i32 red, i32 green, i32 blue, i32 alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

OBDColor::OBDColor(i32 red, i32 green, i32 blue) {
    r = red;
    g = green;
    b = blue;
    a = 1.f;
}

OBDColor::OBDColor(glm::vec4 rgba) {
    r = rgba.r;
    g = rgba.g;
    b = rgba.b;
    a = rgba.a;
}

OBDColor::OBDColor(glm::vec3 rgb) {
    r = rgb.r;
    g = rgb.g;
    b = rgb.b;
    a = 1.f;
}

OBDColor::~OBDColor() {

}

void OBDColor::set(i32 red, i32 green, i32 blue, i32 alpha){
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void OBDColor::set(glm::vec4 v){
    r = v.x;
    g = v.y;
    b = v.z;
    a = v.w;
}

void OBDColor::set(i32 red, i32 green, i32 blue){
    r = red;
    g = green;
    b = blue;
    a = 0;
}

void OBDColor::set(glm::vec3 v){
    r = v.x;
    g = v.y;
    b = v.z;
    a = 0;
}

glm::vec3 OBDColor::getRGB(){
    return glm::vec3(r, g, b);
}

glm::vec4 OBDColor::getRGBA(){
    return glm::vec4(r, g, b, a);
}