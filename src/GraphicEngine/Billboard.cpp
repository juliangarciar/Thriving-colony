#include "Billboard.h"


Billboard::Billboard(SceneNode* parent, Vector3<f32> pos, Color top, Color bot) {
    billboard = Window::Instance() -> getEngine() -> createBillboard(Window::Instance()->getBillboardLayer(), glm::vec3(pos.x, pos.y, pos.z));
	setColor(top, bot);
    setActive(true);
}

Billboard::~Billboard() {
    
}

void Billboard::setColor(Color top, Color bot) {
    OBDColor topColor(top . r, top . g, top . b, top . a);
	OBDColor botColor(bot . r, bot . g, bot . b, bot . a);

    billboard -> setColor(topColor, botColor);
}

void Billboard::setColor(Color t) {
    OBDColor totalColor(t . r, t . g, t . b, t . a);

    billboard -> setColor(totalColor, totalColor);
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

void Billboard::setActive(bool a) {
    //billboard -> setVisible(a);
}