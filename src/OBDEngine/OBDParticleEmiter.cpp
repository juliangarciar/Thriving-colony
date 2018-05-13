#include "OBDParticleEmiter.h"

OBDParticleEmiter::OBDParticleEmiter() {
    type = ParticleEmiterType::Point;
    active = true;
}

OBDParticleEmiter::~OBDParticleEmiter() {
    delete maxStartColor;
    delete minStartColor;
}

void OBDParticleEmiter::emit(i32 now, i32 lastCall, std::vector<TParticle*> particles) {

}

ParticleEmiterType OBDParticleEmiter::getType() {
    return type;
}

glm::vec3 OBDParticleEmiter::getDirection() {
    return direction;
}

glm::vec2 OBDParticleEmiter::getMaxStartSize() {
    return maxStartSize;
}

glm::vec2 OBDParticleEmiter::getMinStartSize() {
    return minStartSize;
}

i32 OBDParticleEmiter::getMaxAngle() {
    return maxAngle;
}

i32 OBDParticleEmiter::getMaxLifeTime() {
    return maxLifeTime;
}

i32 OBDParticleEmiter::getMinLifeTime() {
    return minLifeTime;
}

i32 OBDParticleEmiter::getMaxParticlesPerSecond() {
    return maxParticlesPerSecond;
}

i32 OBDParticleEmiter::getMinParticlesPerSecond() {
    return minParticlesPerSecond;
}

OBDColor* OBDParticleEmiter::getMaxStartColor() {
    return maxStartColor;
}

OBDColor* OBDParticleEmiter::getMinStartColor() {
    return minStartColor;
}

void OBDParticleEmiter::setDirection(glm::vec3 newDirection) {
    direction = newDirection;
}

void OBDParticleEmiter::setMaxStartSize(glm::vec2 newMaxStartSize) {
    maxStartSize = newMaxStartSize;
}

void OBDParticleEmiter::setMinStartSize(glm::vec2 newMinStartSize) {
    minStartSize = newMinStartSize;
}

void OBDParticleEmiter::setMaxAngle(i32 newMaxAngle) {
    maxAngle = newMaxAngle;
}

void OBDParticleEmiter::setMaxLifeTime(i32 newMaxLifeTime) {
    maxLifeTime = newMaxLifeTime;
}

void OBDParticleEmiter::setMinLifeTime(i32 newMinLifeTime) {
    minLifeTime = newMinLifeTime;
}

void OBDParticleEmiter::setMaxParticlesPerSecond(i32 newMaxParticlesPerSecond) {
    maxParticlesPerSecond = newMaxParticlesPerSecond;
}

void OBDParticleEmiter::setMinParticlesPerSecond(i32 newMinParticlesPerSecond) {
    minParticlesPerSecond = newMinParticlesPerSecond;
}

void OBDParticleEmiter::setMaxStartColor(OBDColor* newMaxStartColor) {
    maxStartColor = newMaxStartColor;
}

void OBDParticleEmiter::setMinStartColor(OBDColor* newMinStartColor) {
    minStartColor = newMinStartColor;
}

void OBDParticleEmiter::setActive(bool newActive) {
    active = newActive;
}