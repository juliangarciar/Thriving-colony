#include "Tower.h"

Tower::Tower(int hitPoints, int attackSpeedPnt, int damagePnt, Vector3<float>* pos) : Building(hitPoints, pos, Enumeration::BuildingType::Tower) {
    attackSpeed = attackSpeedPnt;
    damage = damagePnt;

    objetive = 0;
}

Tower::~Tower() {

}