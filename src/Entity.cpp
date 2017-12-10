#include "Entity.h"

Entity::Entity(int hitPoints, Vector3<float>* pos) {
    //ToDo: hacer aumento de felicidad, tropas nivel y tal
    hpMax = hitPoints;
    hp = hpMax;
    position = pos;
}

Entity::~Entity() {
    delete position;
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
