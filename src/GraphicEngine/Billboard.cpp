#include "Billboard.h"
#include "Window.h"

Billboard::Billboard(SceneNode* parent, Vector3<f32> pos, Vector2<f32> size, Color top, Color bot) {
    billboard = Window::Instance() -> getEngine() -> createBillboard(
		Window::Instance()->getBillboardLayer(), 
		Window::Instance()->getBillboardProgram(),
		glm::vec3(pos.x, pos.y, -pos.z), 
		glm::vec2(size.x, size.y)
	);
	setColor(top, bot);
    setActive(true);
}

Billboard::~Billboard() {
    delete billboard;
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

void Billboard::setPosition(Vector3<f32> pos) {
    billboard -> setPosition(glm::vec3(pos.x, pos.y, -pos.z));
}

void Billboard::setSize(Vector2<f32> pos) {
    billboard -> setSize(glm::vec2(pos.x, pos.y));
}

void Billboard::setFrontWidth(f32 i){
	billboard -> setFrontWidth(i);
}

void Billboard::setActive(bool a) {
    billboard -> setActive(a);
}

Vector3<f32> Billboard::getPosition() {
    glm::vec3 pos = billboard -> getPosition();
    return Vector3<f32>(pos.x, pos.y, pos.z);
}