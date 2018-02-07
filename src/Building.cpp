#include "Building.h"
#include "IA.h"
#include "Human.h"
#include "Game.h"

Building::Building(SceneNode *parent, int id, const wchar_t *path, Enumeration::Team team, Enumeration::BreedType breed, Enumeration::BuildingType t, Vector3<float> p) : Entity(parent, id, path, team, breed) {
    buildTimer = 0;
    type = t;

    Init();

    setPosition(p);
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

            maxHP = 1100;
            currentHP = 1100;
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

            maxHP = 720;
            currentHP = 720;
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

            maxHP = 750;
            currentHP = 750;
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

            maxHP = 150;
            currentHP = 150;
            happiness = 1;
            cityLevel = 5;
            citizens = 5;

            buildTimer = 25;
            
            metalCost = Enumeration::BuildingCost::HomeMetalCost;
            crystalCost = Enumeration::BuildingCost::HomeCrystalCost;
        break;
        case Enumeration::BuildingType::MainBuilding:
            // Different color for diferent buildings
            r = 255;
            g = 255;
            b = 255;
 
            maxHP = 3000;
            currentHP = 3000;
        break;
        case Enumeration::BuildingType::Market:
            // Different color for diferent buildings
            r = 2;
            g = 255;
            b = 0;

            maxHP = 600;
            currentHP = 600;
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

            maxHP = 1000;
            currentHP = 1000;
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

            maxHP = 1000;
            currentHP = 1000;
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
            
            maxHP = 550;
            currentHP = 550;
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

            maxHP = 500;
            currentHP = 500;
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

            maxHP = 200;
            currentHP = 200;
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

            maxHP = 800;
            currentHP = 800;
            cityLevel = 15;
            
            buildTimer = 50;
            
            metalCost = Enumeration::BuildingCost::WorkshopMetalCost;
            crystalCost = Enumeration::BuildingCost::WorkshopCrystalCost;
        break;
        default: break;
    }

    //Establece el color base del edificio
    baseColor = video::SColor(255, r, g, b); //ToDo: reemplazar color por material

    finished = false;
    
    //Texture *tex = new Texture("./media/blanco.bmp");
    //Material *m = new Material(tex);
    //this->model->setMaterial(m);
}

void Building::update() {
    if (!finished){
        if (buildTimer <= 0.f) {
            finished = true;
            callback(this);
        } else {
            // This update is called once every second
            buildTimer -= Game::Instance() -> getWindow() -> getDeltaTime();
        }
    }
}

void Building::triggerFinishedCallback(){
    finished = true;
    callback(this);
}

void Building::preTaxPlayer() {
    // Tax the human
    if (team == Enumeration::Team::Human) {
        // Tax costs
        Human::getInstance() -> spendResources(metalCost, crystalCost);
        Human::getInstance() -> increaseCityLevel(cityLevel);  
    } else { // Tax the AI
        // Tax costs
        IA::getInstance() -> spendResources(metalCost, crystalCost);
        IA::getInstance() -> increaseCityLevel(cityLevel); //ToDo: deberia ir en el pos?
    }
}

void Building::posTaxPlayer() {
    // Tax the human
    if (team == Enumeration::Team::Human) {
        // Tax costs
        Human::getInstance() -> increaseHappiness(happiness);
        Human::getInstance() -> increaseCitizens(citizens);   
    } else { // Tax the AI
        // Tax costs
        IA::getInstance() -> increaseHappiness(happiness);
        IA::getInstance() -> increaseCitizens(citizens);   
    }
}

void Building::setFinishedCallback(std::function<void(Building*)> f){
    callback = f;
}

Enumeration::BuildingType Building::getType() { 
    return type;
} 

bool Building::getFinished(){
    return (buildTimer == 0);
}