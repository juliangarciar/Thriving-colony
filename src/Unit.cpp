#include "Unit.h"

Unit::Unit(int hpPnt, int moveSpeedPnt, int attackSpeedPnt, int damagePnt, int attackRangePnt, int viewRangePnt) : Entity(hpPnt) {
    moveSpeed = moveSpeedPnt;
    attackSpeed = attackSpeedPnt;
    damage = damagePnt;
    attackRange = attackRangePnt;
    viewRange = viewRangePnt;

    moving = false;
    attacking = false;

    objetive = 0;
}

Unit::~Unit() {
    delete target;
}

void Unit::attack() {
    if (target != 0) {
        target -> takeDamage(attackDamage);
    }
}

}

Entity* Unit::getObjetive() {
    return objetive;
}

void Unit::setMoving(bool movingPnt) {
    moving = movingPnt;
}

void Unit::setAttacking(bool attackingPnt) {
    attacking = attackingPnt;
}

/*
* Do damage to the objetive
*/
void Unit::attack() {
    objetive -> takeDamage(damage);
}