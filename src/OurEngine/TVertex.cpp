#include "TVertex.h"

TVertex::TVertex(glm::vec3 p, glm::vec3 n, glm::vec2 t) {
    position = p;
    normal = n;
    textureCoordinate = t;
}

TVertex::~TVertex() {

}

glm::vec3 TVertex::getPosition(){
    return position;
}

glm::vec3 TVertex::getNormal(){
    return normal;
}

glm::vec2 TVertex::getTextureCoordinate(){
    return textureCoordinate;
}