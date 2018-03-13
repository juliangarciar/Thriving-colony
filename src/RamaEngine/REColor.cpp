#include "REColor.h"

REColor::REColor(){
    r = 0;
    g = 0;
    b = 0;
    a = 0;
}

REColor::REColor(i32 red, i32 green, i32 blue, i32 alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

REColor::~REColor() {

}

void REColor::set(i32 red, i32 green, i32 blue, i32 alpha){
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void REColor::set(glm::vec4 v){
    r = v.x;
    g = v.y;
    b = v.z;
    a = v.w;
}

void REColor::set(i32 red, i32 green, i32 blue){
    r = red;
    g = green;
    b = blue;
    a = 0;
}

void REColor::set(glm::vec3 v){
    r = v.x;
    g = v.y;
    b = v.z;
    a = 0;
}

glm::vec3 REColor::getRGB(){
    return glm::vec3(r, g, b);
}

glm::vec4 REColor::getRGBA(){
    return glm::vec4(r, g, b, a);
}