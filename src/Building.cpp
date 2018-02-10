#include "Building.h"
#include "IA.h"
#include "Human.h"
#include "Game.h"

Building::Building(SceneNode *parent, i32 id, const wchar_t *path, Enumeration::Team team, Enumeration::BreedType breed, Enumeration::BuildingType t, Vector3<f32> p) : Entity(parent, id, path, team, breed) {
    buildTimer = 0;
    type = t;

    Init();

    setPosition(p);
}

Building::~Building() {
    
}

void Building::Init() {
    f32 r = 0;
    f32 g = 0;
    f32 b = 0;
    switch (type) {
        case Enumeration::BuildingType::Barn:
            // Different color for diferent buildings
            r = 255;
            g = 0;
            b = 0;

            maxHP = 1100;
            currentHP = 1100;
            happiness = Enumeration::HappinessProvided::AmountHappinessBarn;
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
            happiness = Enumeration::HappinessProvided::AmountHappinessBarrack;
            
            buildTimer = 5; //ToDo: antes 40, cambiado para testing

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
            happiness = Enumeration::HappinessProvided::AmountHapppinesHospital;
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
            happiness = Enumeration::HappinessProvided::AmountHappinessHouse;
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
            happiness = Enumeration::HappinessProvided::AmountHappinessMarket;
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
            happiness = Enumeration::HappinessProvided::AmountHappinessQuarry;

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
            happiness = Enumeration::HappinessProvided::AmountHappinessSiderurgy;

            buildTimer = 35;
            
            metalCost = Enumeration::BuildingCost::SiderurgyMetalCost;
            crystalCost = Enumeration::BuildingCost::SiderurgyCrystalCost;
        break;
        case Enumeration::BuildingType::School:
            // Different color for diferent buildings
            r = 0;
            g = 255;
            b = 0;

            this -> buildTimer = 35;
            maxHP = 550;
            currentHP = 550;
            happiness = Enumeration::HappinessProvided::AmountHappinessSchool;
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
            happiness = Enumeration::HappinessProvided::AmountHappinessTower;
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
            happiness = Enumeration::HappinessProvided::AmountHappinessWall;
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
            happiness = Enumeration::HappinessProvided::AmountHappinessWorkshop;
            
            buildTimer = 50;
            
            metalCost = Enumeration::BuildingCost::WorkshopMetalCost;
            crystalCost = Enumeration::BuildingCost::WorkshopCrystalCost;
        break;
        default: break;
    }

    buildTimer = 0; //ToDo: sin tiempo de construcción

    //Establece el color base del edificio
    baseColor = video::SColor(255, r, g, b); //ToDo: reemplazar color por material

    finished = false;
    
    //Texture *tex = new Texture("./media/blanco.bmp");
    //Material *m = new Material(tex);
    //this->model->setMaterial(m);
}

void Building::update() {
    if (!finished){
        if (buildTimer <= 0.0) {
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
        Human::Instance() -> spendResources(metalCost, crystalCost);
        Human::Instance() -> increaseCityLevel(cityLevel);  
    } else { // Tax the AI
        // Tax costs
        IA::Instance() -> spendResources(metalCost, crystalCost);
        IA::Instance() -> increaseCityLevel(cityLevel); //ToDo: deberia ir en el pos?
    }
}

void Building::posTaxPlayer() {
    // Tax the human
    if (team == Enumeration::Team::Human) {
        // Tax costs
        Human::Instance() -> increaseHappiness(happiness);
        Human::Instance() -> increaseCitizens(citizens);   
    } else { // Tax the AI
        // Tax costs
        IA::Instance() -> increaseHappiness(happiness);
        IA::Instance() -> increaseCitizens(citizens);   
    }
}

void Building::setFinishedCallback(std::function<void(Building*)> f){
    callback = f;
}

Enumeration::BuildingType Building::getType() { 
    return type;
} 

bool Building::getFinished(){
    return finished;
}