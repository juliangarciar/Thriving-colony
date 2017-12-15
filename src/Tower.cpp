#include "Tower.h"

Tower::Tower(Vector3<float> *vectorData, Enumeration::Team teamData) : Building(Enumeration::BuildingType::Tower, vectorData, teamData)
{
    attackSpeed = 350;
    damage = 15;

    objetive = 0;
    
}

Tower::~Tower() {
    delete objetive;
}