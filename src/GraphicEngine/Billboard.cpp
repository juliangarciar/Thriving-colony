#include "Billboard.h"


Billboard::Billboard(SceneNode* parent, i32 id, Vector3<f32> pos, Color top, Color bot) {
    scene::ISceneManager *smgr = Window::Instance() -> getSceneManager();
    billboardNode = smgr -> addBillboardSceneNode(
		parent -> getSceneNode(), 
		core::dimension2d<f32>(0, 0),
		core::vector3df(pos.x, pos.y, pos.z), 
		id, 
		video::SColor(top.a, top.r, top.g, top.b), 
		video::SColor(bot.a, bot.r, bot.g, bot.b)
	);
    setActive(true);
}

Billboard::~Billboard() {
    delete billboardNode;
}

void Billboard::setColor(Color top, Color bot) {
    billboardNode -> setColor(video::SColor(top.a, top.r, top.g, top.b), video::SColor(bot.a, bot.r, bot.g, bot.b));
}

void Billboard::setColor(Color totalColor) {
    billboardNode -> setColor(video::SColor(totalColor.a, totalColor.r, totalColor.g, totalColor.b),
                              video::SColor(totalColor.a, totalColor.r, totalColor.g, totalColor.b));
}

void Billboard::setSize(f32 w, f32 h) {
    billboardNode -> setSize(core::dimension2d<f32>(w, h));
    maxSize = w;
}

void Billboard::setID(i32 id) {
    billboardNode -> setID(id);
}

void Billboard::setName(const wchar_t *name) {
    billboardNode -> setName(core::stringw(name).c_str());
}

void Billboard::setPosition(Vector3<f32> pos) {
    billboardNode -> setPosition(core::vector3df(pos.x, pos.y, pos.z));
}

void Billboard::setScale(Vector3<f32> s) {
    billboardNode -> setScale(core::vector3df(s.x, s.y, s.z)); 
}

void Billboard::setScale(f32 s) {
    billboardNode->setSize(core::dimension2d<f32>(maxSize * s, 15.00)); 
}

void Billboard::setRotation(Vector3<f32> r){
    billboardNode->setRotation(core::vector3df(r.x, r.y, r.z));
}

void Billboard::setActive(bool a) {
    billboardNode -> setVisible(a);
}