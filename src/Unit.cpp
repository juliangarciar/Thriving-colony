#include "Unit.h"

Unit::Unit(int hitPoints, Vector3<float>* pos, int _moveSpeed, int _attackSpeed, int damage, int attackRadius, int viewRadius, bool _team, Box3D<float>* hitboxPnt, Model* modelPnt) : Entity(hitPoints, pos, _team, hitboxPnt, modelPnt) {
    moveSpeed = _moveSpeed;
    attackSpeed = _attackSpeed;
    attackDamage = damage;
    attackRange = attackRadius;
    viewRange = viewRadius;

    moving = false;
    attacking = false;

    target = 0;
    battleInvolved = 0;
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

void Unit::assignBattle(Battle* _battle) {
    battleInvolved = _battle;
}

void Unit::updateTarget() {
    if (battleInvolved != NULL) {
        //ToDo: definir como va a ser lo del equipo porque cada uno dice una cosa y ayer se iba a decidir y no se decidio
        //      por ahora esta que siempre es humano 
        target = battleInvolved -> getClosestTarget(*position, Enumeration::Team::Human);
    }
}