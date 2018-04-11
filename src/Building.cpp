#include "Building.h"
#include "Game.h"

#include "Human.h"
#include "IA.h"
#include "GraphicEngine/Window.h"

#define MAX_MAP 10240
#define TOTAL 80

Building::Building(SceneNode *l, i32 id, Enumeration::Team team, Enumeration::BreedType breed, Enumeration::BuildingType t) : Entity(id, team, breed) {
    buildTimer = 0;
    layer = l;
    type = t;
    entityType = Enumeration::EntityType::Building;
    target = NULL;

    Init();
}

Building::~Building() {
}

void Building::Init() {
    /* Box2D parameters */
    Vector2<f32> topLeft;
    Vector2<f32> bottomRight;

    //f32 r = 0;
    //f32 g = 0;
    //f32 b = 0;
    Texture *tex;
    const wchar_t *path;
    Vector3<f32> scale;
    switch (type) {
        case Enumeration::BuildingType::Barn:

            maxHP = 1100;
            currentHP = 1100;
            happiness = Enumeration::HappinessProvided::AmountHappinessBarn;
            cityLevel = 15;

            buildTimer = 50;

            metalCost = Enumeration::BuildingCost::BarnMetalCost;
            crystalCost = Enumeration::BuildingCost::BarnCrystalCost;
            //kCellsX = Enumeration::BuildingCells::BarnCells;
            kCellsX = 2;
            kCellsY = 2;
            path = L"media/buildingModels/barn.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_barn.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_barn_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);
        break;
        case Enumeration::BuildingType::Barrack:

            maxHP = 720;
            currentHP = 720;
            cityLevel = 10;
            happiness = Enumeration::HappinessProvided::AmountHappinessBarrack;
            
            buildTimer = 5; //ToDo: antes 40, cambiado para testing

            metalCost = Enumeration::BuildingCost::BarrackMetalCost;
            crystalCost = Enumeration::BuildingCost::BarrackCrystalCost;
            //kCells = Enumeration::BuildingCells::BarrackCells;
            kCellsX = 4;
            kCellsY = 4;

            path = L"media/buildingModels/barrack.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_barrack.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_barrack_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);
        break;
        case Enumeration::BuildingType::Hospital:

            maxHP = 750;
            currentHP = 750;
            happiness = Enumeration::HappinessProvided::AmountHapppinesHospital;
            cityLevel = 5;

            buildTimer = 60;

            metalCost = Enumeration::BuildingCost::HospitalMetalCost;
            crystalCost = Enumeration::BuildingCost::HospitalCrystalCost;
            //kCells = Enumeration::BuildingCells::HospitalCells;
            kCellsX = 4;
            kCellsY = 4;

            path = L"media/buildingModels/hospital.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_hospital.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_hospital_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);
        break;
        case Enumeration::BuildingType::House:

            maxHP = 150;
            currentHP = 150;
            happiness = Enumeration::HappinessProvided::AmountHappinessHouse;
            cityLevel = 5;
            citizens = 5;

            buildTimer = 25;
            
            metalCost = Enumeration::BuildingCost::HomeMetalCost;
            crystalCost = Enumeration::BuildingCost::HomeCrystalCost;
            //kCells = Enumeration::BuildingCells::HomeCells;
            kCellsX = 1;
            kCellsY = 1;

            path = L"media/buildingModels/house.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_house.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_house_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);
        break;
        case Enumeration::BuildingType::MainBuilding:
 
            maxHP = 3000;
            currentHP = 3000;
            //kCells = Enumeration::BuildingCells::MainCells;
            kCellsX = 5;
            kCellsY = 5;

            path = L"media/buildingModels/command_center.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_command_center.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_command_center_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);
        break;
        case Enumeration::BuildingType::Market:

            maxHP = 600;
            currentHP = 600;
            happiness = Enumeration::HappinessProvided::AmountHappinessMarket;
            cityLevel = 5;

            buildTimer = 60;

            metalCost = Enumeration::BuildingCost::MarketMetalCost;
            crystalCost = Enumeration::BuildingCost::MarketCrystalCost;
            //kCells = Enumeration::BuildingCells::MarketCells;
            kCellsX = 3;
            kCellsY = 4;

            path = L"media/buildingModels/market.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_market.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_market_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);
        break;
        case Enumeration::BuildingType::Quarry:

            maxHP = 1000;
            currentHP = 1000;
            cityLevel = 15;
            happiness = Enumeration::HappinessProvided::AmountHappinessQuarry;

            buildTimer = 35;
            
            //metalCost = Enumeration::BuildingCost::QuarryMetalCost;
            metalCost = 1;
            crystalCost = Enumeration::BuildingCost::QuarryCrystalCost;
            //kCells = Enumeration::BuildingCells::QuarryCells;
            kCellsX = 4;
            kCellsY = 4;

            path = L"media/buildingModels/quarry.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_quarry.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_quarry_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);
        break;
        case Enumeration::BuildingType::Siderurgy:

            maxHP = 1000;
            currentHP = 1000;
            cityLevel = 5;
            happiness = Enumeration::HappinessProvided::AmountHappinessSiderurgy;

            buildTimer = 35;
            
            metalCost = Enumeration::BuildingCost::SiderurgyMetalCost;
            crystalCost = Enumeration::BuildingCost::SiderurgyCrystalCost;
            //kCells = Enumeration::BuildingCells::SiderurgyCells;
            kCellsX = 5;
            kCellsY = 3;

            path = L"media/buildingModels/siderurgy.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_siderurgy.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_siderurgy_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);
        break;
        case Enumeration::BuildingType::School:

            this -> buildTimer = 35;
            maxHP = 550;
            currentHP = 550;
            happiness = Enumeration::HappinessProvided::AmountHappinessSchool;
            cityLevel = 5;

            buildTimer = 35;

            metalCost = Enumeration::BuildingCost::SchoolMetalCost;
            crystalCost = Enumeration::BuildingCost::SchoolCrystalCost;
            //kCells = Enumeration::BuildingCells::SchoolCells;
            kCellsX = 3;
            kCellsY = 2;

            path = L"media/buildingModels/school.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_school.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_school_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);;
        break;
        case Enumeration::BuildingType::Tower:

            maxHP = 500;
            currentHP = 500;
            happiness = Enumeration::HappinessProvided::AmountHappinessTower;
            cityLevel = 5;

            buildTimer = 50;

            metalCost = Enumeration::BuildingCost::TowerMetalCost;
            crystalCost = Enumeration::BuildingCost::TowerCrystalCost;
            //kCells = Enumeration::BuildingCells::TowerCells;
            kCellsX = 1;
            kCellsY = 1;

            path = L"media/buildingModels/tower.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_tower.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_tower_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);
        break;
        case Enumeration::BuildingType::Wall:

            maxHP = 200;
            currentHP = 200;
            happiness = Enumeration::HappinessProvided::AmountHappinessWall;
            cityLevel = 1;

            buildTimer = 10;

            metalCost = Enumeration::BuildingCost::WallMetalCost;
            crystalCost = Enumeration::BuildingCost::WallCrystalCost;
            //kCells = Enumeration::BuildingCells::WallCells;
            kCellsX = 2;
            kCellsY = 1;

            path = L"media/buildingModels/wall.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_wall.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_wall_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);
        break;
        case Enumeration::BuildingType::Workshop:

            maxHP = 800;
            currentHP = 800;
            cityLevel = 15;
            happiness = Enumeration::HappinessProvided::AmountHappinessWorkshop;
            
            buildTimer = 50;
            
            metalCost = Enumeration::BuildingCost::WorkshopMetalCost;
            crystalCost = Enumeration::BuildingCost::WorkshopCrystalCost;
            //kCells = Enumeration::BuildingCells::WorkshopCells;
            kCellsX = 3;
            kCellsY = 4;

            path = L"media/buildingModels/workshop.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_workshop.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_workshop_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);
        break;
        default: break;
    }
    /* Set the 2D hitbox */
    topLeft.x = (kCellsX / 2.0) * (-80.f) + 1;
    topLeft.y = (kCellsY / 2.0) * (-80.f) + 1;
    bottomRight.x = (kCellsX / 2.0) * (80.f) - 1;
    bottomRight.y = (kCellsY / 2.0) * (80.f) - 1;

    hitBox = Box2D(topLeft, bottomRight); 

    setModel(layer, path);
    model->setScale(scale);

    buildTimer = 0; //ToDo: sin tiempo de construcción

    //Establece el color base del edificio
    //ToDo: crear material base

    finished = false;
    
    this->model->setMaterial(new Material(tex));
}

void Building::update() {
    if (!finished){
        if (buildTimer <= 0.0) {
            finished = true;
            callback(this);
        } else {
            // This update is called once every second
            buildTimer -= Window::Instance() -> getDeltaTime();
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