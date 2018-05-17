#include "Billboard.h"


Billboard::Billboard(Vector3<f32> pos) {
    billboard = Window::Instance() -> getEngine() -> createBillboard(glm::vec3(pos.x, pos.y, pos.z));
}

Billboard::~Billboard() {
    
}

void Billboard::setColor(Color* top, Color* bot) {
    OBDColor* topColor = nullptr;
    OBDColor* botColor = nullptr;
    if (top != nullptr) {
        topColor = new OBDColor(top -> r, top -> g, top -> b, top -> a);
    }

    if (bot != nullptr) {
        botColor = new OBDColor(bot -> r, bot -> g, bot -> b, bot -> a);       
    }

    billboard -> setColor(topColor, botColor);
}

void Billboard::setSize(f32 h, f32 tw, f32 bw) {
    billboard -> setSize(h, tw, bw);
}

void Billboard::setPosition(Vector3<f32> pos) {
    billboard -> setPosition(glm::vec3(pos.x, pos.y, pos.z));
}

Vector3<f32> Billboard::getPosition() {
    glm::vec3 pos = billboard -> getPosition();
    return Vector3<f32>(pos.x, pos.y, pos.z);
}

f32 Billboard::getHeight() {
    return billboard -> getHeight();
}

f32 Billboard::getTopWidth() {
    return billboard -> getTopWidth();
}

f32 Billboard::getBottomWidth() {
    return billboard -> getBottomWidth();
}