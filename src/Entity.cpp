#include "Entity.h"

Entity::Entity(int hitPoints) {
    hpMax = hitPoints;
    hp = hpMax;
}

Entity::~Entity() {

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

