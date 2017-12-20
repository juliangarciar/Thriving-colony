#include "Building.h"
#include "IA.h"
#include "Human.h"
#include "Game.h"

Building::Building(int id, SceneNode *parent, Enumeration::BuildingType buildingData, Vector3<float> *pos, Enumeration::Team teamData) : Entity()
{
    int happiness = 0;
    int cityLevel = 0;

    int metalCost = 0;
    int crystalCost = 0;

    float r = 0;
    float g = 0;
    float b = 0;
    switch (buildingData) {
        case Enumeration::BuildingType::Barn:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            this->hpMax = 1100;
            this->hp = 1100;
            happiness = 0;
            cityLevel = 15;

            if (teamData == Enumeration::Team::Human) {
                Human::getInstance() -> setBarnBuilt(true);
			} else {
				IA::getInstance() -> setBarnBuilt(true);
            }

            metalCost = Enumeration::BuildingCost::BarnMetalCost;
            crystalCost = Enumeration::BuildingCost::BarnCrystalCost;

        break;
        case Enumeration::BuildingType::Barrack:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            this->hpMax = 720;
            this->hp = 720;
            happiness = 0;
            cityLevel = 10;
            if (teamData == Enumeration::Team::Human) {
				Human::getInstance() -> setBarrackBuilt(true);
			} else {
				IA::getInstance() -> setBarrackBuilt(true);
            }
            
            metalCost = Enumeration::BuildingCost::BarrackMetalCost;
            crystalCost = Enumeration::BuildingCost::BarrackCrystalCost;

        break;
        case Enumeration::BuildingType::Hospital:
            // Different color for diferent buildings
            r = 0;
            g = 255;
            b = 0;

            this->hpMax = 750;
            this->hp = 750;
            happiness = 40;
            cityLevel = 5;

            metalCost = Enumeration::BuildingCost::HospitalMetalCost;
            crystalCost = Enumeration::BuildingCost::HospitalCrystalCost;

        break;
        case Enumeration::BuildingType::House:
            // Different color for diferent buildings
            r = 0;
            g = 255;
            b = 255;

            this->hpMax = 150;
            this->hp = 150;
            happiness = 1;
            cityLevel = 5;
            //ToDo: Debug cambiar cuando se haga el jugador
            if (teamData == Enumeration::Team::Human) {
				Human::getInstance() -> increaseCitizens();
			} else {
				IA::getInstance() -> increaseCitizens();
            }
            
            metalCost = Enumeration::BuildingCost::HomeMetalCost;
            crystalCost = Enumeration::BuildingCost::HomeCrystalCost;

        break;
        case Enumeration::BuildingType::MainBuilding:
            // Different color for diferent buildings
            r = 255;
            g = 255;
            b = 255;

            this->hpMax = 3000;
            this->hp = 3000;
            happiness = 0;
        break;
        case Enumeration::BuildingType::Market:
            // Different color for diferent buildings
            r = 2;
            g = 255;
            b = 0;

            this->hpMax = 600;
            this->hp = 600;
            happiness = 30;
            cityLevel = 5;

            metalCost = Enumeration::BuildingCost::MarketMetalCost;
            crystalCost = Enumeration::BuildingCost::MarketCrystalCost;

        break;
        case Enumeration::BuildingType::Quarry:
            // Different color for diferent buildings
            r = 0;
            g = 0;
            b = 255;

            this->hpMax = 1000;
            this->hp = 1000;
            happiness = 0;
            cityLevel = 15;

            if (teamData == Enumeration::Team::Human) {
				Human::getInstance() -> increaseQuarryAmount();
			} else {
				IA::getInstance() -> increaseQuarryAmount();
            }
            
            metalCost = Enumeration::BuildingCost::QuarryMetalCost;
            crystalCost = Enumeration::BuildingCost::QuarryCrystalCost;

        break;
        case Enumeration::BuildingType::Siderurgy:
            // Different color for diferent buildings
            r = 0;
            g = 0;
            b = 255;

            this->hpMax = 1000;
            this->hp = 1000;
            happiness = 0;
            cityLevel = 5;

            if (teamData == Enumeration::Team::Human) {
				Human::getInstance() -> increaseSiderurgyAmount();
			} else {
				IA::getInstance() -> increaseSiderurgyAmount();
            }
            
            metalCost = Enumeration::BuildingCost::SiderurgyMetalCost;
            crystalCost = Enumeration::BuildingCost::SiderurgyCrystalCost;

        break;
        case Enumeration::BuildingType::School:
            // Different color for diferent buildings
            r = 0;
            g = 255;
            b = 0;
            
            this->hpMax = 550;
            this->hp = 550;
            happiness = 20;
            cityLevel = 5;

            metalCost = Enumeration::BuildingCost::SchoolMetalCost;
            crystalCost = Enumeration::BuildingCost::SchoolCrystalCost;

        break;
        case Enumeration::BuildingType::Tower:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            this->hpMax = 500;
            this->hp = 500;
            happiness = 1;
            cityLevel = 5;

            metalCost = Enumeration::BuildingCost::TowerMetalCost;
            crystalCost = Enumeration::BuildingCost::TowerCrystalCost;

        break;
        case Enumeration::BuildingType::Wall:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            this->hpMax = 200;
            this->hp = 200;
            happiness = 1;
            cityLevel = 1;

            metalCost = Enumeration::BuildingCost::WallMetalCost;
            crystalCost = Enumeration::BuildingCost::WallCrystalCost;

        break;
        case Enumeration::BuildingType::Workshop:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            this->hpMax = 800;
            this->hp = 800;
            happiness = 0;
            cityLevel = 15;
            if (teamData == Enumeration::Team::Human) {
				Human::getInstance() -> setWorkshopBuilt(true);
			} else {
				IA::getInstance() -> setWorkshopBuilt(true);
            }
            
            metalCost = Enumeration::BuildingCost::WorkshopMetalCost;
            crystalCost = Enumeration::BuildingCost::WorkshopCrystalCost;

        break;
    }

    //ToDo: Graphic engine, this should be in the switch (when models done)
    color = video::SColor(255, r, g, b); //ToDo: esto es fachada 
    
    this->model = new Model(parent, id);
    Window::Instance()->getSceneManager()->getMeshManipulator()->setVertexColors(
        model->getModel()->getMesh(), color
    ); //ToDo: esto es fachada 
    this->model->getModel()->setPosition(pos->getVectorF()); //ToDo: esto es fachada
    this->model->getModel()->setMaterialFlag(video::EMF_LIGHTING, false); //ToDo: esto es fachada

    this->hitbox = new Box3D<float>(this -> model ->getModel() -> getTransformedBoundingBox()); //ToDo: esto es fachada

    this->type = (int)buildingData;
    this->position = pos;

    if (teamData == Enumeration::Team::Human) {
        Human::getInstance() -> increaseHappiness(happiness);
        Human::getInstance() -> increaseCityLevel(cityLevel);
        Human::getInstance() -> spendResources(metalCost, crystalCost);
    } else {
        IA::getInstance() -> increaseHappiness(happiness);
        IA::getInstance() -> increaseCityLevel(cityLevel);
        IA::getInstance() -> spendResources(metalCost, crystalCost);
    }
    //std::cout << this->type << std::endl;
}

Building::~Building() {
    
}

irr::video::SColor Building::getColor() {
    return color;
}

int Building::getType(){ 
    return this->type;
} 
