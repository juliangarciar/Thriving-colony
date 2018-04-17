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
    /* Set the model and texture */
    getModel()->setMaterial(new Material(new Texture(baseData.texturePath.c_str())));

    /* Set the timer */
    buildTimer = new Timer(baseData.buildingTime, false, false);
    buildTimer -> setCallback([&]{
		returnToOriginalMaterial();
        adjustCityStats();
        if (callback != nullptr) callback(this);
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
        Human::Instance() -> increaseCitizens(getCitizensVariation());   
        Human::Instance() -> increaseCityLevel(cityLevel);
    } else {
        IA::Instance() -> increaseHappiness(getHappinessVariation());
        IA::Instance() -> increaseCitizens(getCitizensVariation());   
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