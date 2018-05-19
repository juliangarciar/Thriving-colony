#include "TParticle.h"

TParticle::TParticle(OBDColor newColor, OBDColor newStartColor, i32 newEndTime, i32 newStartTime, glm::vec3 newPosition, glm::vec3 newStartDirection, glm::vec3 newDirection, glm::vec2 newSize, glm::vec2 newStartSize) {
    color = newColor;
    startColor = newStartColor;

    endTime = newEndTime;
    i32 startTime = newStartTime;

    position = newPosition;
    startDirection = newStartDirection;
    direction = newDirection;
    size = newSize;
    startSize = newStartSize;
}

TParticle::~TParticle() {

}

void TParticle::setColor(OBDColor newColor) {
    color = newColor;
}

void TParticle::setStartColor(OBDColor newStartColor) {
    startColor = newStartColor;
}

void TParticle::setEndTime(i32 newEndTime) {
    endTime = newEndTime;
}

void TParticle::setStartTime(i32 newStartTime) {
    startTime = newStartTime;
}

void TParticle::setPosition(glm::vec3 newPosition) {
    position = newPosition;
}
        
void TParticle::setStartDirection(glm::vec3 newStartDirection) {
    startDirection = newStartDirection;
}

void TParticle::setDirection(glm::vec3 newDirection) {
    direction =newDirection;
}

void TParticle::setSize(glm::vec2 newSize) {
    size = newSize;
}

void TParticle::setStartSize(glm::vec2 newStartSize) {
    startSize = newStartSize;
}