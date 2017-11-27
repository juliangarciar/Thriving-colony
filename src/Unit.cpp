#include "Unit.h"

Unit::Unit(int hitPoints, int _moveSpeed, int _attackSpeed, int _damage) : Entity(hitPoints) {
    moveSpeed = _moveSpeed;
    attackSpeed = _attackSpeed;
    attackDamage = _damage;
    target = 0;
}

Unit::~Unit() {
    delete target;
}

void Unit::attack() {
    if (target != 0) {
        target -> takeDamage(attackDamage);
    }
}

void Unit::updateTarget(Entity* newTarget) {
    if (newTarget != 0) {
        target = newTarget;
    }
}