#include "Building.h"
#include "IA.h"
#include "Human.h"
#include "Game.h"

Building::Building(int id, SceneNode *parent, Enumeration::BuildingType buildingData, Vector3<float> vectorData, Enumeration::Team teamData) : Entity(parent, id)
{
    this->happiness = 0;
    this->cityLevel = 0;

    this->metalCost = 0;
    this->crystalCost = 0;

    this->stepsToBuild = 0;
    this->currentStep = 0;

    bool initialBuilding = false;

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
            this->happiness = 0;
            this->cityLevel = 15;

            this->stepsToBuild = 50;

            this->metalCost = Enumeration::BuildingCost::BarnMetalCost;
            this->crystalCost = Enumeration::BuildingCost::BarnCrystalCost;

        break;
        case Enumeration::BuildingType::Barrack:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            this->hpMax = 720;
            this->hp = 720;
            this->happiness = 0;
            this->cityLevel = 10;
            
            this->stepsToBuild = 40;

            this->metalCost = Enumeration::BuildingCost::BarrackMetalCost;
            this->crystalCost = Enumeration::BuildingCost::BarrackCrystalCost;

        break;
        case Enumeration::BuildingType::Hospital:
            // Different color for diferent buildings
            r = 0;
            g = 255;
            b = 0;

            this->hpMax = 750;
            this->hp = 750;
            this->happiness = 40;
            this->cityLevel = 5;

            this->stepsToBuild = 60;

            this->metalCost = Enumeration::BuildingCost::HospitalMetalCost;
            this->crystalCost = Enumeration::BuildingCost::HospitalCrystalCost;

        break;
        case Enumeration::BuildingType::House:
            // Different color for diferent buildings
            r = 0;
            g = 255;
            b = 255;

            this->hpMax = 150;
            this->hp = 150;
            this->happiness = 1;
            this->cityLevel = 5;

            this->stepsToBuild = 25;
            
            
            this->metalCost = Enumeration::BuildingCost::HomeMetalCost;
            this->crystalCost = Enumeration::BuildingCost::HomeCrystalCost;

        break;
        case Enumeration::BuildingType::MainBuilding:
            // Different color for diferent buildings
            r = 255;
            g = 255;
            b = 255;
 
            this->hpMax = 3000;
            this->hp = 3000;

            this->stepsToBuild = 0;
            initialBuilding = true;

            this->hpMax = 3000;
            this->hp = 3000;
        break;
        case Enumeration::BuildingType::Market:
            // Different color for diferent buildings
            r = 2;
            g = 255;
            b = 0;

            this->hpMax = 600;
            this->hp = 600;
            this->happiness = 30;
            this->cityLevel = 5;

            this->stepsToBuild = 60;

            this->metalCost = Enumeration::BuildingCost::MarketMetalCost;
            this->crystalCost = Enumeration::BuildingCost::MarketCrystalCost;

        break;
        case Enumeration::BuildingType::Quarry:
            // Different color for diferent buildings
            r = 0;
            g = 0;
            b = 255;

            this->hpMax = 1000;
            this->hp = 1000;
            this->happiness = 0;
            this->cityLevel = 15;

            this->stepsToBuild = 35;
            
            this->metalCost = Enumeration::BuildingCost::QuarryMetalCost;
            this->crystalCost = Enumeration::BuildingCost::QuarryCrystalCost;

        break;
        case Enumeration::BuildingType::Siderurgy:
            // Different color for diferent buildings
            r = 0;
            g = 0;
            b = 255;

            this->hpMax = 1000;
            this->hp = 1000;
            this->happiness = 0;
            this->cityLevel = 5;

            this->stepsToBuild = 35;
            // If this is the first siderurgy, build it instantly
            if (teamData == Enumeration::Team::Human) {
                if (Human::getInstance() -> getSiderurgyAmount() == 0) {
                    this->stepsToBuild = 0;
                    initialBuilding = true;
                    Human::getInstance() -> increaseSiderurgyAmount();  
                }
            }else{
                if (IA::getInstance() -> getSiderurgyAmount() == 0) {
                    this->stepsToBuild = 0;
                    initialBuilding = true;
                    IA::getInstance() -> increaseSiderurgyAmount();  
                }
            }
            
            this->metalCost = Enumeration::BuildingCost::SiderurgyMetalCost;
            this->crystalCost = Enumeration::BuildingCost::SiderurgyCrystalCost;

        break;
        case Enumeration::BuildingType::School:
            // Different color for diferent buildings
            r = 0;
            g = 255;
            b = 0;
            
            this->hpMax = 550;
            this->hp = 550;
            this->happiness = 20;
            this->cityLevel = 5;

            this->stepsToBuild = 35;

            this->metalCost = Enumeration::BuildingCost::SchoolMetalCost;
            this->crystalCost = Enumeration::BuildingCost::SchoolCrystalCost;

        break;
        case Enumeration::BuildingType::Tower:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            this->hpMax = 500;
            this->hp = 500;
            this->happiness = 1;
            this->cityLevel = 5;

            this->stepsToBuild = 50;

            this->metalCost = Enumeration::BuildingCost::TowerMetalCost;
            this->crystalCost = Enumeration::BuildingCost::TowerCrystalCost;

        break;
        case Enumeration::BuildingType::Wall:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            this->hpMax = 200;
            this->hp = 200;
            this->happiness = 1;
            this->cityLevel = 1;

            this->stepsToBuild = 10;

            this->metalCost = Enumeration::BuildingCost::WallMetalCost;
            this->crystalCost = Enumeration::BuildingCost::WallCrystalCost;

        break;
        case Enumeration::BuildingType::Workshop:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            this->hpMax = 800;
            this->hp = 800;
            this->happiness = 0;
            this->cityLevel = 15;
            
            this->stepsToBuild = 50;
            
            this->metalCost = Enumeration::BuildingCost::WorkshopMetalCost;
            this->crystalCost = Enumeration::BuildingCost::WorkshopCrystalCost;

        break;
    }
    

    //ToDo: Graphic engine, this should be in the switch (when models done)
    this->baseColor = video::SColor(255, r, g, b); //ToDo: esto es fachada 
    if (initialBuilding) {
        this->currentColor = video::SColor(255, r, g, b);
        this -> finished = true;
    } else {
        // DEBUG SOLO PARA LA PRESENTACION
        //
        //
        this -> stepsToBuild = 3;
        //
        //
        // DEBUG SOLO PARA LA PRESENTACION
        this->currentColor = video::SColor(255, 0, 0, 0);
        this -> finished = false;
    }
    Window::Instance()->getSceneManager()->getMeshManipulator()->setVertexColors(
        this->model->getModel()->getMesh(), baseColor
    ); //ToDo: esto es fachada 

    this->setPosition(vectorData);
    this->hitbox->set(this -> model ->getModel() -> getTransformedBoundingBox()); //ToDo: esto es fachada

    this->type = (int)buildingData;
    // Tax the IA the moment it builds the building
    // The player should be taxed when actually building the building
    if (teamData == Enumeration::Team::IA) {
        taxPlayer(teamData);
    }
    //std::cout << this->type << std::endl;
    
}



Building::~Building() {
    delete model;
}

// This update is called once every second
void Building::update() {
    std::cout << currentStep << "/" << stepsToBuild << "=" << finished << std::endl;
    if (!finished) {
        currentStep ++;
        if (currentStep >= stepsToBuild) {
            Window::Instance()->getSceneManager()->getMeshManipulator()->setVertexColors(
                this->model->getModel()->getMesh(), baseColor
            );
            // Increase stuff when the human ends the building, but do so for the AI
            // when it places the building. is it fair? i dunno
            if (team == Enumeration::Team::Human) {
                specialTax(team);
		        Game::Instance() -> getEvents() -> triggerEvent(Enumeration::EventType::EnableText);
            }            
            this -> finished = true;
        }
    }
}

irr::video::SColor Building::getColor() {
    return baseColor;
}

int Building::getType(){ 
    return this->type;
} 

/**
 * This method taxes the costs of a building to the player that builds it
 * be it the human or the AI 
 */
void Building::taxPlayer(Enumeration::Team teamData) {
    
    // Tax the human
    if (teamData == Enumeration::Team::Human) {
        // Tax costs
        Human::getInstance() -> increaseHappiness(happiness);
        Human::getInstance() -> increaseCityLevel(cityLevel);
        Human::getInstance() -> spendResources(metalCost, crystalCost);
        

    // Tax the AI
    } else {
        // Tax costs
        IA::getInstance() -> increaseHappiness(happiness);
        IA::getInstance() -> increaseCityLevel(cityLevel);
        IA::getInstance() -> spendResources(metalCost, crystalCost);
        // Increae levels and stuff when built by the ai, instead of waiting for the building to finish building
        specialTax(teamData);
    }
    Window::Instance()->getSceneManager()->getMeshManipulator()->setVertexColors(
        this->model->getModel()->getMesh(), currentColor
    );   
    
}

void Building::specialTax(Enumeration::Team teamData) {
        // Tax the human
    if (teamData == Enumeration::Team::Human) {
        
        // Special taxes
        switch ((Enumeration::BuildingType)type) {
            case Enumeration::BuildingType::Barn:
                    Human::getInstance() -> setBarnBuilt(true);                
            break;
            case Enumeration::BuildingType::Barrack:
                    Human::getInstance() -> setBarrackBuilt(true);                
            break;            
            case Enumeration::BuildingType::House:
                    Human::getInstance() -> increaseCitizens();                
            break;            
            case Enumeration::BuildingType::Quarry:
                    Human::getInstance() -> increaseQuarryAmount();                
            break;
            case Enumeration::BuildingType::Siderurgy:
                    Human::getInstance() -> increaseSiderurgyAmount();                
            break;                
            case Enumeration::BuildingType::Workshop:
                    Human::getInstance() -> setWorkshopBuilt(true);                
            break;
        }

    // Tax the AI
    } else {
        
        // Special taxes
        switch ((Enumeration::BuildingType)type) {
            case Enumeration::BuildingType::Barn:
                IA::getInstance() -> setBarnBuilt(true);                
            break;
            case Enumeration::BuildingType::Barrack:
                IA::getInstance() -> setBarrackBuilt(true);                
            break;            
            case Enumeration::BuildingType::House:
                IA::getInstance() -> increaseCitizens();               
            break;            
            case Enumeration::BuildingType::Quarry: 
                IA::getInstance() -> increaseQuarryAmount();                
            break;
            case Enumeration::BuildingType::Siderurgy:
                IA::getInstance() -> increaseSiderurgyAmount();                
            break;                  
            case Enumeration::BuildingType::Workshop:
                IA::getInstance() -> setWorkshopBuilt(true);                
            break;
        }
    }
}

bool Building::getFinished() {
    return finished;
}

int Building::getID() {
    return ID;
}