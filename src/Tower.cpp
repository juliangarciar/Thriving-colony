#include "Tower.h"

Tower::Tower(Vector3<float> *vectorData, bool teamData) : Building(Enumeration::BuildingType::Tower, vectorData, teamData)
{
    attackSpeed = 350;
    damage = 15;

    objetive = 0;
    
}

Tower::~Tower() {
    delete objetive;
}