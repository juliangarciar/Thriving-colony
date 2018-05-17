#include "Building.h"
#include "Game.h"

#include "Human.h"
#include "IA.h"
#include "GraphicEngine/Window.h"

Building::Building(SceneNode *_layer,
                i32 _id, 
                Enumeration::Team _team, 
                BuildingData baseData):Entity(
                _layer,
                _id,
                _team,
                Enumeration::EntityType::Building,
                baseData.maxHP,
                baseData.viewRadius,
                baseData.attackRange,
                baseData.attackDamage,
                baseData.attackSpeed,
                baseData.metalCost,
                baseData.crystalCost,
                baseData.happinessVariation,
                baseData.citizensVariation,
                baseData.cellsX,
                baseData.cellsY,
                baseData.modelPath,
                baseData.texturePath
                ), 
                cityLevel(baseData.cityLevel),
                buildingType(baseData.type),
                callback(nullptr)
{
    /* Set the timer */
    buildTimer = new Timer(baseData.buildingTime, false, false);
    buildTimer -> setCallback([&]{
        adjustCityStats();
        if (callback != nullptr) callback(this);
    });

	//ToDo: hacia abajo anadido por rafa
    f32 billBoardOffset = 200.00;

	Vector3<f32> pos(getPosition().x, Map::Instance()->getTerrain()->getY(getPosition().x,getPosition().y) + billBoardOffset, getPosition().y);

    barBg = new Billboard(layer, ID, pos, Color(0,0,0,255), Color(0,0,0,255));
	bar = new Billboard(layer, ID, pos, Color(0, 255, 0, 255), Color(0, 255, 0, 255));
    barBg -> setSize(105.00, 15.00);
}

Building::~Building() {
    delete buildTimer;
    delete barBg;
    delete bar;
    //delete particle;
}

void Building::startBuilding() {
    taxPlayer();
    buildTimer -> start();
}

void Building::taxPlayer(){
    //Tax the player
    if (getTeam() == Enumeration::Team::Human) {
        Human::Instance() -> spendResources(getMetalCost(), getCrystalCost());
    } else {
        IA::Instance() -> spendResources(getMetalCost(), getCrystalCost());
    }
}

void Building::adjustCityStats() {
    // Adjust the stats of the player
    if (getTeam() == Enumeration::Team::Human) {
        Human::Instance() -> increaseHappiness(getHappinessVariation());
        Human::Instance() -> increasePersons(getCitizensVariation());   
        Human::Instance() -> increaseCityLevel(cityLevel);
    } else {
        IA::Instance() -> increaseHappiness(getHappinessVariation());
        IA::Instance() -> increasePersons(getCitizensVariation());   
        IA::Instance() -> increaseCityLevel(cityLevel);
    }
}

void Building::setFinishedCallback(std::function<void(Building*)> f){
    callback = f;
}

bool Building::getFinished(){
    return buildTimer->isFinished();
}

std::string Building::getType(){
    return buildingType;
}

void Building::setCantBuildColor() {
	baseMat -> setColor(Color(0, 0, 255, 255));
    model -> setMaterial(baseMat);
}

void Building::debugAnimation(std::string path) {
    std::string name = "modelo1";
    std::vector<std::string> * vector = new std::vector<std::string>();
    vector -> push_back(path);
    std::map< std::string, std::vector < std::string > > * frames = new std::map< std::string, std::vector < std::string > > ();

    frames->insert(std::pair< std::string, std::vector<std::string>>(name, *vector));

    anim = new Animation(frames);
}