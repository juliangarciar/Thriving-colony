#include "Billboard.h"


Billboard::Billboard(SceneNode* parent, i32 id, Vector3<f32> pos) {
    scene::ISceneManager *smgr = Window::Instance() -> getSceneManager();
    billboardNode = smgr -> addBillboardSceneNode(parent -> getSceneNode(), core::dimension2d<f32>(100.00, 10.00), core::vector3df(pos.x, pos.y, pos.z), id, video::SColor(255, 0, 0, 0), video::SColor(255, 0, 0, 0));
    setActive(true);
}

Billboard::~Billboard() {
    delete billboardNode;
}

void Billboard::setColor(video::SColor top, video::SColor bot) {
    billboardNode -> setColor(top, bot);
}

void Billboard::setSize(f32 w, f32 h) {
    billboardNode -> setSize(core::dimension2d<f32>(w, h));
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

void Billboard::rotate(f32 x, f32 y){
    double param = atan(y / x) * 180 / PI;
    //if(x < 0 && y < 0)
    //    param += 180;
    //else if(x < 0)
    //    param += 90;
    //else if(y < 0)
    //    param += 270;
    billboardNode->setRotation(core::vector3df(0, param, 0));
}
void Billboard::setActive(bool a) {
    billboardNode -> setVisible(a);
}