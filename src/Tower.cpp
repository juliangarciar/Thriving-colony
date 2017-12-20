#include "Tower.h"

<<<<<<< HEAD
Tower::Tower(Vector3<float> *vectorData, Enumeration::Team teamData) : Building(Enumeration::BuildingType::Tower, vectorData, teamData)
=======
Tower::Tower(SceneNode *parent, Vector3<float> *vectorData, bool teamData) : Building(parent, Enumeration::BuildingType::Tower, vectorData, teamData)
>>>>>>> GraphicEngine
{
    attackSpeed = 350;
    damage = 15;

    objetive = 0;
    
}

Tower::~Tower() {
    delete objetive;
}