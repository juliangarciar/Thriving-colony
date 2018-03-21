#include "OBDEColor.h"

OBDEColor::OBDEColor(){
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}

OBDEColor::OBDEColor(i32 red, i32 green, i32 blue, i32 alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

OBDEColor::~OBDEColor() {

}

void OBDEColor::set(i32 red, i32 green, i32 blue, i32 alpha){
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void OBDEColor::set(glm::vec4 v){
    r = v.x;
    g = v.y;
    b = v.z;
    a = v.w;
}

void OBDEColor::set(i32 red, i32 green, i32 blue){
    r = red;
    g = green;
    b = blue;
    a = 0;
}

void OBDEColor::set(glm::vec3 v){
    r = v.x;
    g = v.y;
    b = v.z;
    a = 0;
}

glm::vec3 OBDEColor::getRGB(){
    return glm::vec3(r, g, b);
}

glm::vec4 OBDEColor::getRGBA(){
    return glm::vec4(r, g, b, a);
}