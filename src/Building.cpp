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

std::string Building::getType(){
    return data.type;
}