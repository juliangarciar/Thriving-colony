#include "Tower.h"

Tower::Tower(Vector3<float> *vectorData, bool teamData, Model *modelData ,Box3D<float> *boxData) : Building(Enumeration::BuildingType::Tower, vectorData, teamData, modelData, boxData)
{
    attackSpeed = 350;
    damage = 15;

    objetive = 0;
}

Tower::~Tower() {
    delete objetive;
}