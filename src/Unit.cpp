#include "Unit.h"

Unit::Unit(int hpPnt, int moveSpeedPnt, int attackSpeedPnt, int damagePnt) : Entity(hpPnt) {
    moveSpeed = moveSpeedPnt;
    attackSpeed = attackSpeedPnt;
    damage = damagePnt;
}

Unit::~Unit() {

}