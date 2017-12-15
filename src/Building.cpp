#include "Building.h"
#include "IA.h"
#include "Human.h"

Building::Building(Enumeration::BuildingType buildingData, Vector3<float> *vectorData, Enumeration::Team teamData, Model *modelData, Box3D<float> *boxData) : Entity()
{
    switch (buildingData) {
        case Enumeration::BuildingType::Barn:
            this->hpMax = 1100;
            this->hp = 1100;
            this -> happiness = 0;
            if (teamData == Enumeration::Team::Human) {
                Human::getInstance() -> setBarnBuilt(true);
                Human::getInstance() -> increaseHappiness(happiness);
			} else {
				IA::getInstance() -> setBarnBuilt(true);
            }
        break;
        case Enumeration::BuildingType::Barrack:
            this->hpMax = 720;
            this->hp = 720;
            this -> happiness = 0;
            if (teamData == Enumeration::Team::Human) {
				Human::getInstance() -> setBarrackBuilt(true);
			} else {
				IA::getInstance() -> setBarrackBuilt(true);
			}
        break;
        case Enumeration::BuildingType::Hospital:
            this->hpMax = 750;
            this->hp = 750;
            this -> happiness = 15;
            break;
        case Enumeration::BuildingType::House:
            this->hpMax = 150;
            this->hp = 150;
            this -> happiness = 1;
        break;
        case Enumeration::BuildingType::MainBuilding:
            this->hpMax = 3000;
            this->hp = 3000;
            this -> happiness = 0;
        break;
        case Enumeration::BuildingType::Market:
            this->hpMax = 600;
            this->hp = 600;
            this -> happiness = 10;
        break;
        case Enumeration::BuildingType::Quarry:
            this->hpMax = 1000;
            this->hp = 1000;
            this -> happiness = 0;
        break;
        case Enumeration::BuildingType::Siderurgy:
            this->hpMax = 1000;
            this->hp = 1000;
            this -> happiness = 0;
        break;
        case Enumeration::BuildingType::School:
            this->hpMax = 550;
            this->hp = 550;
            this -> happiness = 5;
        break;
        case Enumeration::BuildingType::Tower:
            this->hpMax = 500;
            this->hp = 500;
            this -> happiness = 1;
        break;
        case Enumeration::BuildingType::Wall:
            this->hpMax = 200;
            this->hp = 200;
            this -> happiness = 1;
        break;
        case Enumeration::BuildingType::Workshop:
            this->hpMax = 800;
            this->hp = 800;
            this -> happiness = 0;
            if (teamData == Enumeration::Team::Human) {
				Human::getInstance() -> setWorkshopBuilt(true);
			} else {
				IA::getInstance() -> setWorkshopBuilt(true);
			}
        break;
    }
    //Graphic engine, this should be in the switch (when models done)
    this->model = modelData;
    this->hitbox = boxData;
    this->type = buildingData;
    this->position = vectorData;
    if (teamData == Enumeration::Team::Human) {
        Human::getInstance() -> increaseHappiness(happiness);
    } else {
        IA::getInstance() -> increaseHappiness(happiness);
    }
}

Building::~Building() {
    
}
