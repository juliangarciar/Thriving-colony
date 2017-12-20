#include "Building.h"
#include "IA.h"
#include "Human.h"
#include "Game.h"

Building::Building(int id, SceneNode *parent, Enumeration::BuildingType buildingData, Vector3<float> *pos, Enumeration::Team teamData) : Entity()
{
    int happiness = 0;
    int cityLevel = 0;
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
                Human::getInstance() -> increaseHappiness(happiness);
			} else {
				IA::getInstance() -> setBarnBuilt(true);
            }
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
        break;
        case Enumeration::BuildingType::Hospital:
            // Different color for diferent buildings
            r = 0;
            g = 255;
            b = 0;

            this->hpMax = 750;
            this->hp = 750;
            happiness = 15;
            cityLevel = 5;
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
            happiness = 10;
            cityLevel = 5;
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

        break;
        case Enumeration::BuildingType::School:
            // Different color for diferent buildings
            r = 0;
            g = 255;
            b = 0;
            
            this->hpMax = 550;
            this->hp = 550;
            happiness = 5;
            cityLevel = 5;
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
        break;
    }

    //ToDo: Graphic engine, this should be in the switch (when models done)
    color = video::SColor(255, r, g, b); //ToDo: esto es fachada 
    this->model = new Model(parent, id);

    Window::Instance()->getSceneManager()->getMeshManipulator()->setVertexColors(
        model->getModel()->getMesh(), color
    ); //ToDo: esto es fachada 

    this->type = (int)buildingData;
    this->position = pos;
    if (teamData == Enumeration::Team::Human) {
        Human::getInstance() -> increaseHappiness(happiness);
        Human::getInstance() -> increaseCityLevel(cityLevel);
    } else {
        IA::getInstance() -> increaseHappiness(happiness);
        IA::getInstance() -> increaseCityLevel(cityLevel);
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
