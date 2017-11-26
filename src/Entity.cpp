#include "Entity.h"

Entity::Entity(int hitPoints, int attackDmg) {
    hpMax = hitPoints;
    hp = hpMax;
    attackDamage = attackDmg;
}

Entity::~Entity() {
    delete target;
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

void Entity::attack() {
    if (target != 0) {
        target -> takeDamage(attackDamage);
    }
}