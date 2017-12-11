#include "Entity.h"

Entity::Entity(int hitPoints, Vector3<float>* pos, bool _team, Box3D<float>* hitboxPnt, Model* modelPnt) {
    //ToDo: hacer aumento de felicidad, tropas nivel y tal
    hpMax = hitPoints;
    hp = hpMax;
    position = pos;
    team = _team;
    hitbox = hitboxPnt;
    model = modelPnt;
}

Entity::~Entity() {
    delete position;
    delete hitbox;
    delete model;
}

int Entity::getHP() {
    return hp;
}

/*
* Decreases Hp
* dmg = quantity of hp to drecrease
*/
void Entity::takeDamage(int dmg) {
    hp = hp-dmg;
    if (hp <= 0) {
        hp = 0;
        die();
    }
}

void Entity::die() {
    delete this;
}

Vector3<float>* Entity::getPosition() {
    return position;
}

Box3D<float>* Entity::getHitbox() {
    return hitbox;
}

Model* Entity::getModel() {
    return model;
}