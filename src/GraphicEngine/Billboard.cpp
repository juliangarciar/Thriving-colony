#include "Billboard.h"


Billboard::Billboard(SceneNode* parent, i32 id, Vector3<f32> pos, Color top, Color bot) {
    
    setActive(true);
}

Billboard::~Billboard() {
    
}

void Billboard::setColor(Color top, Color bot) {
   
}

void Billboard::setSize(f32 w, f32 h) {
    
}

void Billboard::setID(i32 id) {
    
}

void Billboard::setName(const wchar_t *name) {
    
}

void Billboard::setPosition(Vector3<f32> pos) {
    
}

void Billboard::setScale(Vector3<f32> s) {
    
}

void Billboard::rotate(f32 x, f32 y){
    double param = atan(y / x) * 180 / PI;
    
    
}
void Billboard::setActive(bool a) {
    
}