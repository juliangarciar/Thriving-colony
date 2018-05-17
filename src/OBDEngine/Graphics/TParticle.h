#ifndef TPARTICLE_H
#define TPARTICLE_H

#include "../OBDColor.h"

struct TParticle {
    OBDColor color;
    OBDColor startColor;

    i32 endTime;
    i32 startTime;
    
    glm::vec3 position;
    glm::vec3 startDirection;
    glm::vec3 direction;
    glm::vec2 size;
    glm::vec2 startSize;
};

#endif