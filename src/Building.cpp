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
		setBaseMaterial();
        adjustCityStats();
        if (callback != nullptr) callback(this);
    });

	//ToDo: hacia abajo anadido por rafa
    f32 billBoardOffset = 200.00;

	Texture *t = new Texture(baseData.texturePath.c_str());

    /* Set the model and texture */
    baseMat = new Material(t);
    baseMat -> setColor(255, 255, 255, 255);

    damagedMat = new Material(t);
    damagedMat -> setColor(255, 255, 0, 0);
    
    canBuildMat = new Material(t);
    canBuildMat -> setColor(128, 0, 255, 0);

    cantBuildMat = new Material(t);
    cantBuildMat -> setColor(128, 255, 0, 0);

    setBaseMaterial();

    Vector3<f32> bp = Vector3<f32>(getPosition().x, 200.00, getPosition().y);
    barBg = new Billboard(layer, ID, bp);
    bar = new Billboard(layer, ID, bp);
    barBg -> setPosition(bp);
    bp.z -= 1;
    bar -> setPosition(bp);
    bar -> setColor(irr::video::SColor(255, 0, 255, 0),irr::video::SColor(255, 0, 255, 0));

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

//ToDo: hacia abajo anadido por rafa
void Building::setCanBuildMat() {
    model -> setMaterial(canBuildMat);
}

void Building::setCantBuildMat() {
    model -> setMaterial(cantBuildMat);
}