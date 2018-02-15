#include "TLight.h"

TLight::TLight() : TEntity(){

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