#include "Building.h"
#include "Game.h"

#include "Human.h"
#include "IA.h"
#include "GraphicEngine/Window.h"

Building::Building(SceneNode *_layer, i32 _id, Enumeration::Team _team, BuildingData baseData) : 
    Entity(
        _layer,
        _id,
        _team,
        Enumeration::EntityType::Unit,
        baseData.maxHP,
        baseData.viewRadius,
        baseData.attackRange,
        baseData.attackDamage,
        baseData.attackSpeed,
        baseData.metalCost,
        baseData.crystalCost,
        baseData.happinessVariation,
        baseData.citizensVariation,
        1,
        1,
        baseData.modelPath,
        baseData.texturePath
    )
{
    finished = false;
    callback = nullptr;

    /* Set the model and texture */
    getModel()->setMaterial(new Material(new Texture(baseData.texturePath.c_str())));

    /* Set the timer */
    buildTimer = new Timer(baseData.buildTime, false, false);
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
    if (getTeam() == Enumeration::Team::Human) {
        Human::Instance() -> spendResources(getMetalCost(), getCrystalCost());
    } else {
        IA::Instance() -> spendResources(getMetalCost(), getCrystalCost());
    }
}

void Building::adjustCityStats() {
    // Tax the human
    if (getTeam() == Enumeration::Team::Human) {
        // Tax costs
        Human::Instance() -> increaseHappiness(getHappinessVariation());
        Human::Instance() -> increaseCitizens(getCitizensVariation());   
        Human::Instance() -> increaseCityLevel(cityLevel); //ToDo: deberia ir en el pos?
    } else { // Tax the AI
        // Tax costs
        IA::Instance() -> increaseHappiness(getHappinessVariation());
        IA::Instance() -> increaseCitizens(getCitizensVariation());   
        IA::Instance() -> increaseCityLevel(cityLevel); //ToDo: deberia ir en el pos?
    }
}

void Building::setFinishedCallback(std::function<void(Building*)> f){
    callback = f;
}

bool Building::getFinished(){
    return finished;
}

std::string Building::getType(){
    return data.type;
}