#include "TVertex.h"

TVertex::TVertex(Vector3<f32> p, Vector3<f32> n, Vector2<f32> t) {
    position = p;
    normal = n;
    textureCoordinate = t;
}

TVertex::~TVertex() {

}

Vector3<f32> TVertex::getPosition(){
    return position;
}

Vector3<f32> TVertex::getNormal(){
    return normal;
}

Vector2<f32> TVertex::getTextureCoordinate(){
    return textureCoordinate;
}