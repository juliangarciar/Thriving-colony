#include "Building.h"
#include "IA.h"
#include "Human.h"
#include "Game.h"

Building::Building(int id, SceneNode *parent, const wchar_t *path, Enumeration::BuildingType buildingType, Vector3<float> vectorData, Enumeration::Team teamData) : Entity(parent, id, path)
{
    happiness = 0;
    cityLevel = 0;

    metalCost = 0;
    crystalCost = 0;

    buildTimer = 0;

    type = buildingType;
    team = teamData;

    Init();

    setPosition(vectorData);
    hitbox -> set(model -> getBoundingBox() . getAABBox3D());

    // Tax the IA the moment it builds the building
    // The player should be taxed when actually building the building
    if (teamData == Enumeration::Team::IA) {
        taxPlayer(teamData);
    }
}

Building::~Building() {
    
}

void Building::Init() {
    float r = 0;
    float g = 0;
    float b = 0;
    switch (type) {
        case Enumeration::BuildingType::Barn:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            hpMax = 1100;
            hp = 1100;
            happiness = 0;
            cityLevel = 15;

            buildTimer = 50;

            metalCost = Enumeration::BuildingCost::BarnMetalCost;
            crystalCost = Enumeration::BuildingCost::BarnCrystalCost;

        break;
        case Enumeration::BuildingType::Barrack:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            hpMax = 720;
            hp = 720;
            happiness = 0;
            cityLevel = 10;
            
            buildTimer = 40;

            metalCost = Enumeration::BuildingCost::BarrackMetalCost;
            crystalCost = Enumeration::BuildingCost::BarrackCrystalCost;

        break;
        case Enumeration::BuildingType::Hospital:
            // Different color for diferent buildings
            r = 0;
            g = 255;
            b = 0;

            hpMax = 750;
            hp = 750;
            happiness = 40;
            cityLevel = 5;

            buildTimer = 60;

            metalCost = Enumeration::BuildingCost::HospitalMetalCost;
            crystalCost = Enumeration::BuildingCost::HospitalCrystalCost;

        break;
        case Enumeration::BuildingType::House:
            // Different color for diferent buildings
            r = 0;
            g = 255;
            b = 255;

            hpMax = 150;
            hp = 150;
            happiness = 1;
            cityLevel = 5;

            buildTimer = 25;
            
            metalCost = Enumeration::BuildingCost::HomeMetalCost;
            crystalCost = Enumeration::BuildingCost::HomeCrystalCost;

        break;
        case Enumeration::BuildingType::MainBuilding:
            // Different color for diferent buildings
            r = 255;
            g = 255;
            b = 255;
 
            hpMax = 3000;
            hp = 3000;

            buildTimer = 0;

            hpMax = 3000;
            hp = 3000;
        break;
        case Enumeration::BuildingType::Market:
            // Different color for diferent buildings
            r = 2;
            g = 255;
            b = 0;

            hpMax = 600;
            hp = 600;
            happiness = 30;
            cityLevel = 5;

            buildTimer = 60;

            metalCost = Enumeration::BuildingCost::MarketMetalCost;
            crystalCost = Enumeration::BuildingCost::MarketCrystalCost;

        break;
        case Enumeration::BuildingType::Quarry:
            // Different color for diferent buildings
            r = 0;
            g = 0;
            b = 255;

            hpMax = 1000;
            hp = 1000;
            happiness = 0;
            cityLevel = 15;

            buildTimer = 35;
            
            metalCost = Enumeration::BuildingCost::QuarryMetalCost;
            crystalCost = Enumeration::BuildingCost::QuarryCrystalCost;

        break;
        case Enumeration::BuildingType::Siderurgy:
            // Different color for diferent buildings
            r = 0;
            g = 0;
            b = 255;

            hpMax = 1000;
            hp = 1000;
            happiness = 0;
            cityLevel = 5;

            buildTimer = 35;
            
            metalCost = Enumeration::BuildingCost::SiderurgyMetalCost;
            crystalCost = Enumeration::BuildingCost::SiderurgyCrystalCost;

        break;
        case Enumeration::BuildingType::School:
            // Different color for diferent buildings
            r = 0;
            g = 255;
            b = 0;
            
            hpMax = 550;
            hp = 550;
            happiness = 20;
            cityLevel = 5;

            buildTimer = 35;

            metalCost = Enumeration::BuildingCost::SchoolMetalCost;
            crystalCost = Enumeration::BuildingCost::SchoolCrystalCost;

        break;
        case Enumeration::BuildingType::Tower:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            hpMax = 500;
            hp = 500;
            happiness = 1;
            cityLevel = 5;

            buildTimer = 50;

            metalCost = Enumeration::BuildingCost::TowerMetalCost;
            crystalCost = Enumeration::BuildingCost::TowerCrystalCost;

        break;
        case Enumeration::BuildingType::Wall:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            hpMax = 200;
            hp = 200;
            happiness = 1;
            cityLevel = 1;

            buildTimer = 10;

            metalCost = Enumeration::BuildingCost::WallMetalCost;
            crystalCost = Enumeration::BuildingCost::WallCrystalCost;

        break;
        case Enumeration::BuildingType::Workshop:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            hpMax = 800;
            hp = 800;
            happiness = 0;
            cityLevel = 15;
            
            buildTimer = 50;
            
            metalCost = Enumeration::BuildingCost::WorkshopMetalCost;
            crystalCost = Enumeration::BuildingCost::WorkshopCrystalCost;

        break;
        default: break;
    }

    //ToDo: Graphic engine, this should be in the switch (when models done)
    baseColor = video::SColor(255, r, g, b); //ToDo: reemplazar color por material
    currentColor = video::SColor(255, 0, 0, 0); //ToDo: reemplazar color por material
    finished = false;
    
    //Texture *tex = new Texture("./media/blanco.bmp");
    //Material *m = new Material(tex);
    //this->model->setMaterial(m);
}

// This update is called once every second
void Building::update() {
    if (!finished) {
        if (buildTimer <= 0) {
            callback();
            finished = true;
        } else {
            buildTimer -= Game::Instance() -> getWindow() -> getDeltaTime();
        }
    }
}
void Building::triggerFinishedCallback(){
    callback();
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
    } else { // Tax the AI
        // Tax costs
        IA::getInstance() -> increaseHappiness(happiness);
        IA::getInstance() -> increaseCityLevel(cityLevel);
        IA::getInstance() -> spendResources(metalCost, crystalCost);
        // Increae levels and stuff when built by the ai, instead of waiting for the building to finish building
        specialTax(teamData);
    }
    //ToDo: reemplazar color por material
    setColor(currentColor);
}

void Building::specialTax(Enumeration::Team teamData) {
    // Tax the human
    if (teamData == Enumeration::Team::Human) {
        // Special taxes
        switch (type) {
            case Enumeration::BuildingType::Barn:
                //Human::getInstance() -> setBarnBuilt(true);                
            break;
            case Enumeration::BuildingType::Barrack:
                //Human::getInstance() -> setBarrackBuilt(true);                
            break;            
            case Enumeration::BuildingType::House:
                Human::getInstance() -> increaseCitizens();                
            break;            
            case Enumeration::BuildingType::Quarry:
                //Human::getInstance() -> increaseQuarryAmount();                
            break;
            case Enumeration::BuildingType::Siderurgy:
                //Human::getInstance() -> increaseSiderurgyAmount();                
            break;                
            case Enumeration::BuildingType::Workshop:
                //Human::getInstance() -> setWorkshopBuilt(true);                
            break;
            //ToDo: incrementar felicidad
            default: break;
        }
    } else { // Tax the AI
        // Special taxes
        switch ((Enumeration::BuildingType)type) {
            case Enumeration::BuildingType::Barn:
                //IA::getInstance() -> setBarnBuilt(true);                
            break;
            case Enumeration::BuildingType::Barrack:
                //IA::getInstance() -> setBarrackBuilt(true);                
            break;            
            case Enumeration::BuildingType::House:
                IA::getInstance() -> increaseCitizens();               
            break;            
            case Enumeration::BuildingType::Quarry: 
                //IA::getInstance() -> increaseQuarryAmount();                
            break;
            case Enumeration::BuildingType::Siderurgy:
                //IA::getInstance() -> increaseSiderurgyAmount();                
            break;                  
            case Enumeration::BuildingType::Workshop:
                //IA::getInstance() -> setWorkshopBuilt(true);                
            break;
            //ToDo: incrementar felicidad
            default: break;
        }
    }
}

void Building::setFinishedCallback(std::function<void()> f){
    callback = f;
}

Enumeration::BuildingType Building::getType() { 
    return type;
} 

bool Building::getFinished() {
    return finished;
}

int Building::getID() {
    return ID;
}