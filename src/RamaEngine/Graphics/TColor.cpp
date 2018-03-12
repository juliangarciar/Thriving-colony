#include "TColor.h"

TColor::TColor(){
    
}

TColor::TColor(i32 red, i32 green, i32 blue, i32 alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

TColor::~TColor() {

}

void TColor::set(i32 red, i32 green, i32 blue, i32 alpha){
    r = red;
    g = green;
    b = blue;
    a = alpha;
}