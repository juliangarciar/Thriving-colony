#include "Building.h"
#include "Game.h"

Building::Building(SceneNode *l, i32 id, Enumeration::Team team, Enumeration::BreedType breed, Enumeration::BuildingType t) : Entity(id, team, breed) {
    buildTimer = 0;
    layer = l;
    type = t;

    Init();
}

Building::~Building() {
    
}

void Building::Init() {
    f32 r = 0;
    f32 g = 0;
    f32 b = 0;
    const wchar_t *path;
    Vector3<f32> scale;
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
            kCells = Enumeration::BuildingCells::BarnCells;

            path = L"media/buildingModels/establo.obj";
            scale = Vector3<f32>(25,25,25);
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
            kCells = Enumeration::BuildingCells::BarrackCells;

            path = L"media/buildingModels/barraca.obj";
            scale = Vector3<f32>(25,25,25);
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
            kCells = Enumeration::BuildingCells::HospitalCells;

            path = L"media/buildingModels/hospital.obj";
            scale = Vector3<f32>(64,64,64);
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
            kCells = Enumeration::BuildingCells::HomeCells;

            path = L"media/buildingModels/house.obj";
            scale = Vector3<f32>(64,64,64);
        break;
        case Enumeration::BuildingType::MainBuilding:
            // Different color for diferent buildings
            r = 255;
            g = 255;
            b = 255;
 
            maxHP = 3000;
            currentHP = 3000;
            kCells = Enumeration::BuildingCells::MainCells;

            path = L"media/buildingModels/command_center.obj";
            scale = Vector3<f32>(48,48,48);
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
            kCells = Enumeration::BuildingCells::MarketCells;

            path = L"media/buildingModels/mercado.obj";
            scale = Vector3<f32>(25,25,25);
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
            kCells = Enumeration::BuildingCells::QuarryCells;

            path = L"media/buildingModels/cantera.obj";
            scale = Vector3<f32>(25,25,25);
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
            kCells = Enumeration::BuildingCells::SiderurgyCells;

            path = L"media/buildingModels/escuela.obj";
            scale = Vector3<f32>(25,25,25);
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
            kCells = Enumeration::BuildingCells::SchoolCells;

            path = L"media/buildingModels/siderurgia.obj";
            scale = Vector3<f32>(25,25,25);
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
            kCells = Enumeration::BuildingCells::TowerCells;

            path = L"media/buildingModels/torre_vigilancia.obj";
            scale = Vector3<f32>(25,25,25);
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
            kCells = Enumeration::BuildingCells::WallCells;

            path = L"media/buildingModels/muralla.obj";
            scale = Vector3<f32>(25,25,25);
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
            kCells = Enumeration::BuildingCells::WorkshopCells;

            path = L"media/buildingModels/taller_maquinas_de_asedio.obj";
            scale = Vector3<f32>(25,25,25);
        break;
        default: break;
    }

    setModel(layer, path);
    model->setScale(scale);

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