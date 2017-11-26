#include "Entity.h"

Entity::Entity(int hpPnt) {
    hp = hpPnt;
}

Entity::~Entity() {

}

int Entity::getHP() {
    return hp;
}

/*
* Decreases Hp
* h = quantity of hp to drecrease
*/
void Entity::decreaseHP(int h) {
    hp = hp-h;
    if (hp < 0) {
        hp = 0;
    }
}