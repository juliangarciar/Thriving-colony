#include "Tower.h"

Tower::Tower(int hitPoints, Vector3<float>* pos, bool _team, Box3D<float>* hitboxPnt, Model* modelPnt) : Building(hitPoints, pos, Enumeration::BuildingType::Tower, _team, hitboxPnt, modelPnt) {
    attackSpeed = 350;
    damage = 15;

    objetive = 0;
}

Tower::~Tower() {
    delete objetive;
}