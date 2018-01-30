#include "Tower.h"

Tower::Tower(int id, SceneNode *parent, const wchar_t *path, Vector3<float> vectorData, Enumeration::Team teamData) : Building(id, parent, path, Enumeration::BuildingType::Tower, vectorData, teamData)
{
    attackSpeed = 350;
    damage = 15;

    objetive = 0;
    
}

Tower::~Tower() {
    delete objetive;
}