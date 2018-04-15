#include "Building.h"
#include "Game.h"

#include "Human.h"
#include "IA.h"
#include "GraphicEngine/Window.h"

#define MAX_MAP 10240
#define TOTAL 80

Building::Building(SceneNode *l, i32 id, Enumeration::Team team, BuildingData d) : Entity(id, team, Enumeration::EntityType::Building) {
    layer = l;

    finished = false;

    callback = nullptr;

    target = nullptr;

    //ToDo: load from JSON

    /* Set the model and texture */
    //setModel(layer, modelPath);
    //Texture *tex = new Texture(texturePath);
    //this->model->setMaterial(new Material(tex)); //ToDo: crear material inicial
	/* Establece su color original */
	//ToDo: establece el material por defecto

    /* Box2D parameters */
    Vector2<f32> topLeft;
    Vector2<f32> bottomRight;

    /* Set the 2D hitbox params */
    topLeft.x = (kCellsX / 2.0) * (-80.f) + 1;
    topLeft.y = (kCellsY / 2.0) * (-80.f) + 1;
    bottomRight.x = (kCellsX / 2.0) * (80.f) - 1;
    bottomRight.y = (kCellsY / 2.0) * (80.f) - 1;

    /* Set the 2D hitbox */
    hitBox = Box2D(topLeft, bottomRight); 

    /* Set the timer */
    buildTimer = new Timer(d.buildTime, false, false);
    buildTimer -> setCallback([&]{
		//ToDo: volver al material original
        adjustCityStats();
        if (callback != nullptr) callback(this);
        finished = true;
    });
}

Building::~Building() {
    delete buildTimer;
}

void Building::update() {
    buildTimer -> tick();
}

void Building::startBuilding() {
    taxPlayer();
    buildTimer -> start();
}

void Building::taxPlayer(){
    //Tax the player
    if (team == Enumeration::Team::Human) {
        Human::Instance() -> spendResources(metalCost, crystalCost);
    } else {
        IA::Instance() -> spendResources(metalCost, crystalCost);
    }
}

void Building::adjustCityStats() {
    // Tax the human
    if (team == Enumeration::Team::Human) {
        // Tax costs
        Human::Instance() -> increaseCityLevel(cityLevel);  
        Human::Instance() -> increaseHappiness(happinessVariation);
        Human::Instance() -> increaseCitizens(citizensVariation);   
    } else { // Tax the AI
        // Tax costs
        IA::Instance() -> increaseHappiness(happinessVariation);
        IA::Instance() -> increaseCitizens(citizensVariation);   
        IA::Instance() -> increaseCityLevel(cityLevel); //ToDo: deberia ir en el pos?
    }
}

void Building::setFinishedCallback(std::function<void(Building*)> f){
    callback = f;
}

bool Building::getFinished(){
    return finished;
}






    /*switch (buildingType) {
        case Enumeration::BuildingType::Barn:

            maxHP = 1100;
            currentHP = 1100;
            happiness = Enumeration::HappinessProvided::AmountHappinessBarn;
            cityLevel = 15;

            buildTime = 50.0;

            metalCost = Enumeration::BuildingCost::BarnMetalCost;
            crystalCost = Enumeration::BuildingCost::BarnCrystalCost;
            //kCellsX = Enumeration::BuildingCells::BarnCells;
            kCellsX = 2;
            kCellsY = 2;
            modelPath = L"media/buildingModels/barn.obj";
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
            
            buildTime = 5.0; //Antes 40 ahora cambiado a 5 para testeo
            
            metalCost = Enumeration::BuildingCost::BarrackMetalCost;
            crystalCost = Enumeration::BuildingCost::BarrackCrystalCost;
            //kCells = Enumeration::BuildingCells::BarrackCells;
            kCellsX = 4;
            kCellsY = 4;

            modelPath = L"media/buildingModels/barrack.obj";
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

            buildTime = 60.0;
            
            metalCost = Enumeration::BuildingCost::HospitalMetalCost;
            crystalCost = Enumeration::BuildingCost::HospitalCrystalCost;
            //kCells = Enumeration::BuildingCells::HospitalCells;
            kCellsX = 4;
            kCellsY = 4;

            modelPath = L"media/buildingModels/hospital.obj";
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

            buildTime = 25.0;
            
            metalCost = Enumeration::BuildingCost::HomeMetalCost;
            crystalCost = Enumeration::BuildingCost::HomeCrystalCost;
            //kCells = Enumeration::BuildingCells::HomeCells;
            kCellsX = 1;
            kCellsY = 1;

            modelPath = L"media/buildingModels/house.obj";
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

            modelPath = L"media/buildingModels/command_center.obj";
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

            buildTime = 60.0;
            
            metalCost = Enumeration::BuildingCost::MarketMetalCost;
            crystalCost = Enumeration::BuildingCost::MarketCrystalCost;
            //kCells = Enumeration::BuildingCells::MarketCells;
            kCellsX = 3;
            kCellsY = 4;

            modelPath = L"media/buildingModels/market.obj";
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

            buildTime = 35.0;
            
            //metalCost = Enumeration::BuildingCost::QuarryMetalCost;
            metalCost = 1;
            crystalCost = Enumeration::BuildingCost::QuarryCrystalCost;
            //kCells = Enumeration::BuildingCells::QuarryCells;
            kCellsX = 4;
            kCellsY = 4;

            modelPath = L"media/buildingModels/quarry.obj";
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

            buildTime = 35.0;
            
            metalCost = Enumeration::BuildingCost::SiderurgyMetalCost;
            crystalCost = Enumeration::BuildingCost::SiderurgyCrystalCost;
            //kCells = Enumeration::BuildingCells::SiderurgyCells;
            kCellsX = 5;
            kCellsY = 3;

            modelPath = L"media/buildingModels/siderurgy.obj";
            if(breed == Enumeration::BreedType::Drorania){
                tex = new Texture("./media/textures/Drorania/drorania_siderurgy.jpg");
            }
            else{
                tex = new Texture("./media/textures/Kaonov/kaonov_siderurgy_Base_Color.jpg");
            }
            scale = Vector3<f32>(1,1,1);
        break;
        case Enumeration::BuildingType::School:

            
            maxHP = 550;
            currentHP = 550;
            happiness = Enumeration::HappinessProvided::AmountHappinessSchool;
            cityLevel = 5;

            buildTime = 35.0;
            
            metalCost = Enumeration::BuildingCost::SchoolMetalCost;
            crystalCost = Enumeration::BuildingCost::SchoolCrystalCost;
            //kCells = Enumeration::BuildingCells::SchoolCells;
            kCellsX = 3;
            kCellsY = 2;

            modelPath = L"media/buildingModels/school.obj";
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

            buildTime = 50.0;
            
            metalCost = Enumeration::BuildingCost::TowerMetalCost;
            crystalCost = Enumeration::BuildingCost::TowerCrystalCost;
            //kCells = Enumeration::BuildingCells::TowerCells;
            kCellsX = 1;
            kCellsY = 1;

            modelPath = L"media/buildingModels/tower.obj";
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

            buildTime = 10.0;
            
            metalCost = Enumeration::BuildingCost::WallMetalCost;
            crystalCost = Enumeration::BuildingCost::WallCrystalCost;
            //kCells = Enumeration::BuildingCells::WallCells;
            kCellsX = 2;
            kCellsY = 1;

            modelPath = L"media/buildingModels/wall.obj";
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
            
            buildTime = 50.0;
            
            metalCost = Enumeration::BuildingCost::WorkshopMetalCost;
            crystalCost = Enumeration::BuildingCost::WorkshopCrystalCost;
            //kCells = Enumeration::BuildingCells::WorkshopCells;
            kCellsX = 3;
            kCellsY = 4;

            modelPath = L"media/buildingModels/workshop.obj";
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
    
        //Metal and crystal costs of each building.
        enum BuildingCost {
            SchoolMetalCost = 500,
            SchoolCrystalCost = 0,

            MarketMetalCost = 800,
            MarketCrystalCost = 0,

            HospitalMetalCost = 800,
            HospitalCrystalCost = 0,

            SiderurgyMetalCost = 500,
            SiderurgyCrystalCost = 0,

            QuarryMetalCost = 2000,
            QuarryCrystalCost = 0,

            HomeMetalCost = 100,
            HomeCrystalCost = 0,

            BarrackMetalCost = 500,
            BarrackCrystalCost = 0,

            BarnMetalCost = 675,
            BarnCrystalCost = 230,

            WorkshopMetalCost = 725,
            WorkshopCrystalCost = 300,

            WallMetalCost = 75,
            WallCrystalCost = 0,

            TowerMetalCost = 300,
            TowerCrystalCost = 0,
        };

        //Cells occupied by each building.
        enum BuildingCells{
            MainCells = 3,
            SchoolCells = 2,
            MarketCells = 2,
            HospitalCells = 3,
            SiderurgyCells = 3,
            QuarryCells = 3,
            HomeCells = 1,
            BarrackCells = 3,
            BarnCells = 2,
            WorkshopCells = 2,
            WallCells = 1,
            TowerCells = 1

        };

        //
        enum BuildingHalfsize{
            MainHalfsize = 120,
            SchoolHalfsize = 80,
            MarketHalfsize = 80,
            HospitalHalfsize = 120,
            SiderurgyHalfsize = 120,
            QuarryHalfsize = 120,
            HomeHalfsize = 40,
            BarrackHalfsize = 80,
            BarnHalfsize = 80,
            WorkshopHalfsize = 80,
            WallHalfsize = 40,
            TowerHalfsize = 40
        };

        //Amount of happiness provided by each building.
        enum HappinessProvided {
            AmountHappinessBarn = 0,
            AmountHappinessBarrack = 0,
            AmountHapppinesHospital = 40,
            AmountHappinessHouse = 1,
            AmountHappinessMarket = 30,
            AmountHappinessQuarry = 0,
            AmountHappinessSchool = 20,
            AmountHappinessSiderurgy = 0,
            AmountHappinessTower = 1,
            AmountHappinessWall = 1,
            AmountHappinessWorkshop = 0
        };
    */