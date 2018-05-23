#include "Building.h"
#include "Game.h"

#include "Human.h"
#include "IA.h"
#include "GraphicEngine/Window.h"
#include "BuildingManager.h"
#include <WorldEngine/WorldGeometry.h>
#include <SoundEngine/SoundSystem.h>

Building::Building(
	SceneNode *_layer,
	i32 _id, 
	Enumeration::Team _team, 
	BuildingData baseData,
	BuildingManager* _buildingManager) :
		Entity(
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
			baseData.bbOffset
		), 
		cityLevel(baseData.cityLevel),
		buildingType(baseData.type),
		buildingTime(baseData.buildingTime),
		callback(nullptr),
		buildingManager(_buildingManager)
{
    // Set the building timer
    buildTimer = new Timer(baseData.buildingTime, false, false);
    buildTimer -> setCallback([&]{
        adjustCityStats();
		setBaseColor();
        if(team == Enumeration::Team::Human){
            SoundSystem::Instance() -> stopVoiceEvent();
            SoundSystem::Instance() -> playVoiceEvent("endBuilding");
        }
        if (callback != nullptr) callback(this);
    });
}

Building::~Building() {
    WorldGeometry::Instance() -> clearBuildingCell(this);
    delete buildTimer;
    buildTimer = nullptr;
}

void Building::startBuilding() {
    taxPlayer();
	model -> setColor(Color(0, 1, 0, 1));
    buildTimer -> start();
}

void Building::taxPlayer() {
    //Tax the player
    if (getTeam() == Enumeration::Team::Human) {
        Human::Instance() -> spendResources(getMetalCost(), getCrystalCost());
    } else {
        IA::Instance() -> spendResources(getMetalCost(), getCrystalCost());
        IA::Instance() -> modifyHappinessInComing(getHappinessVariation());
        IA::Instance() -> modifyMaxPeopleInComing(getCitizensVariation());   
        IA::Instance() -> modifyCityLevelInComing(cityLevel);
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
        IA::Instance() -> modifyHappinessInComing(- getHappinessVariation());
        IA::Instance() -> modifyMaxPeopleInComing(- getCitizensVariation());   
        IA::Instance() -> modifyCityLevelInComing(- cityLevel);
    }
}

void Building::setFinishedCallback(std::function<void(Building*)> f) {
    callback = f;
}

bool Building::getFinished() {
    return buildTimer->isFinished();
}

std::string Building::getType() {
    return buildingType;
}

//ToDo: revisar billboards
void Building::takeDamage(i32 _damage) {
    f32 percentage(0);
    currentHP = currentHP - _damage;
    
    if (currentHP < 1) {
        buildingManager->deleteBuilding(ID);
        return;
    }
    else {
        percentage = (float)currentHP / (float)maxHP;
		bar->setFrontWidth(percentage);
		bar->setFrontColor(Color(1.f-percentage, percentage, 0));
        tookDamageTimer -> restart();
        // Tint the model red
        setDamageColor();
    }
}

void Building::setTarget(Entity *newTarget) {
    target = newTarget;
}

void Building::setCantBuildColor() {
	model -> setColor(Color(0, 0, 1, 1));
}

i32 Building::getBuildingTime() {
	return buildingTime;
}

std::vector< Vector2<f32> > Building::getInnerComponentsPosition() const{
    std::vector< Vector2<f32> > dummy;
    dummy.push_back(vectorPos);
    return dummy;
}