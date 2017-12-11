#include "Tower.h"

Tower::Tower(int hitPoints, int attackSpeedPnt, int damagePnt, Vector3<float>* pos, bool _team) : Building(hitPoints, pos, Enumeration::BuildingType::Tower, _team) {
    attackSpeed = attackSpeedPnt;
    damage = damagePnt;

    objetive = 0;
}

Tower::~Tower() {
    delete objetive;
}