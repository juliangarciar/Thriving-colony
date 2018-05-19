#include "Building.h"
#include "Game.h"

#include "Human.h"
#include "IA.h"
#include "GraphicEngine/Window.h"
#include "BuildingManager.h"

Building::Building(SceneNode *_layer,
                i32 _id, 
                Enumeration::Team _team, 
                BuildingData baseData,
                BuildingManager* _buildingManager):Entity(
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
                                                callback(nullptr),
                                                buildingManager(_buildingManager)
{
    // Set the building timer
    buildTimer = new Timer(baseData.buildingTime, false, false);
    buildTimer -> setCallback([&]{
        adjustCityStats();
		setBaseColor();
        if (callback != nullptr) callback(this);
    });
}

Building::~Building() {
    delete buildTimer;
    buildTimer = nullptr;
}

void Building::startBuilding() {
    taxPlayer();
	model -> setColor(Color(0, 255, 0, 255));
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
        Human::Instance() -> modifyHappiness(getHappinessVariation());
        Human::Instance() -> modifyMaxPeople(getCitizensVariation());   
        Human::Instance() -> modifyCityLevel(cityLevel);
    } else {
        IA::Instance() -> modifyHappiness(getHappinessVariation());
        IA::Instance() -> modifyMaxPeople(getCitizensVariation());   
        IA::Instance() -> modifyCityLevel(cityLevel);
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

void Building::takeDamage(i32 _damage) {
    currentHP = currentHP - _damage;
    if(currentHP < 1){
        currentHP = 0;
        std::cout << "Soy un edificio y me muero \n";
        buildingManager->deleteBuilding(ID);
        return;
    }
    else{
        tookDamageTimer -> restart();
        // Tint the model red
        setDamageColor();
    }
}

void Building::setTarget(Entity *newTarget) {
    target = newTarget;
}

void Building::setCantBuildColor() {
	model -> setColor(Color(0, 0, 255, 255));
}