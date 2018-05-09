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

		//ToDo: separar datos de la app
		f32 billBoardOffset = 200.00;

		Vector3<f32> pos(getPosition().x, Map::Instance()->getTerrain()->getY(getPosition().x,getPosition().y) + billBoardOffset, getPosition().y);

		barBg = new Billboard(layer, ID, pos, Color(0,0,0,255), Color(0,0,0,255));
		bar = new Billboard(layer, ID, pos, Color(0, 255, 0, 255), Color(0, 255, 0, 255));
		barBg -> setSize(105.00, 15.00);
		////////////////////////////

        if (callback != nullptr) callback(this);
    });


	Texture *t = new Texture(baseData.texturePath.c_str());

    /* Set the model and texture */
    baseMat = new Material(t);
    baseMat -> setColor(Color(255, 255, 255, 255));

    damagedMat = new Material(t);
    damagedMat -> setColor(Color(255, 255, 0, 0));
    
    canBuildMat = new Material(t);
    canBuildMat -> setColor(Color(128, 0, 255, 0));

    cantBuildMat = new Material(t);
    cantBuildMat -> setColor(Color(128, 255, 0, 0));

    setBaseMaterial();
}

Building::~Building() {
    delete canBuildMat;
    delete cantBuildMat;
    delete baseMat;
    delete damagedMat;
    delete buildTimer;
    delete barBg;
    delete bar;
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