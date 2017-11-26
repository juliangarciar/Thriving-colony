#include "Tower.h"

Tower::Tower(int hpPnt, int attackSpeedPnt, int damagePnt) : Building(hpPnt) {
    attackSpeed = attackSpeedPnt;
    damage = damagePnt;
}

Tower::~Tower() {

}