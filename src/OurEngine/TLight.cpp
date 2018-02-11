#include "TLight.h"

TLight::TLight(){

}

TLight::~TLight(){

}

void TLight::beginDraw(){

}

void TLight::endDraw(){

}

void TLight::setIntensity(TColor c){
    intensity = c;
}

TColor TLight::getIntensity(){
    return intensity;
}