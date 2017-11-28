#include "Unit.h"

Unit::Unit(int hpPnt, int moveSpeedPnt, int attackSpeedPnt, int damagePnt, int attackRangePnt, int viewRangePnt) : Entity(hpPnt) {
    moveSpeed = moveSpeedPnt;
    attackSpeed = attackSpeedPnt;
    attackDamage = damagePnt;
    attackRange = attackRangePnt;
    viewRange = viewRangePnt;

    moving = false;
    attacking = false;

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

Entity* Unit::getTarget() {
    return target;
}

void Unit::setMoving(bool movingPnt) {
    moving = movingPnt;
}

void Unit::setAttacking(bool attackingPnt) {
    attacking = attackingPnt;
}

