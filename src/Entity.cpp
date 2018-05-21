#include "Entity.h"
#include "Map.h"
#include <MathEngine/Vector3.h>
#include <GraphicEngine/Model.h>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Window.h>
#include "UnitManager.h"

Entity::Entity(SceneNode* _layer,
                i32 _id,
                Enumeration::Team _team,
                Enumeration::EntityType _type,
                i32 _maxHP,
                i32 _maxView,
                i32 _attackRange,
                i32 _attackDamage,
                i32 _attackSpeed,
                i32 _metal,
                i32 _crystal,
                i32 _happines,
                i32 _citizens,
                i32 _cellsX,
                i32 _cellsY,
                std::string _modelPath,
                f32 _bbOffset) : 
                    ID(_id),
                    team(_team),
                    entityType(_type),
                    model(nullptr),
                    vectorPos(0,0),
                    hitBox(Vector2<f32>(0, 0),
                        Vector2<f32>(_cellsX * cSize,
                                        _cellsY * cSize)),
                    currentHP(_maxHP),
                    maxHP(_maxHP), 
                    viewRadius(_maxView),
                    attackRange(_attackRange),
                    attackDamage(_attackDamage),
                    attackSpeed(_attackSpeed),
                    metalCost(_metal), 
                    crystalCost(_crystal), 
                    happinessVariation(_happines), 
                    citizensVariation(_citizens),
                    target(nullptr),
                    hostile(std::vector< Entity* >(0)),
                    bbOffset(_bbOffset)
{
    //set Timer
    tookDamageTimer = new Timer(0.1);
    tookDamageTimer -> setCallback([&]() {
        setBaseColor();
    });

    //Set model
    model = new Model(_layer, _id, _modelPath);

	// Set the color
    setBaseColor();
	Vector3<f32> pos(
		getPosition().x, 
		Map::Instance()->getTerrain()->getY(getPosition().x,getPosition().y) + bbOffset, 
		getPosition().y
	);

	Vector2<f32> size(hitBox.Right() - hitBox.Left() * 0.8f, 40.00);
    bar = new Billboard(_layer, pos, size, Color(0,0,0,1), Color(0,1,0,1));
	bar->setFrontWidth(0.5);
}

Entity::~Entity() {
    if (target != nullptr) {
        target -> removeHostile(this);
    }
    putHostileTargetsToNull();
    if (model != nullptr) {
        delete model;
    }
    hostile.clear();
    
    delete tookDamageTimer;

	//Billboard
    delete bar;
	//
    for (std::size_t i = 0; i < hostile.size(); i++) {
        delete hostile[i];
    }
    hostile.clear();
}

void Entity::addHostile(Entity* newHostileUnit) {
    hostile.push_back(newHostileUnit);
}

void Entity::removeHostile(Entity* oldHostileUnit) {
    bool done = false;
    for (std::size_t i = 0; i < hostile.size() && done == false; i++) {
        if (hostile[i] == oldHostileUnit) {
            hostile.erase(hostile.begin() + i);
            done = true;
        }
    }
}

void Entity::putHostileTargetsToNull() {
    for (std::size_t i = 0; i < hostile.size(); i++) {
        hostile[i] -> setTarget(nullptr);
    }
}

//SETTERS
void Entity::setID(i32 id) {
    ID = id;
    model -> setID(id);
}

void Entity::setPosition(Vector2<f32> vectorData) {
    vectorPos = vectorData;

    model -> setPosition(Vector3<f32>(vectorData.x, Map::Instance() -> getTerrain() -> getY(vectorData.x, vectorData.y), vectorData.y));
	//std::cout << vectorData.x << " " << Map::Instance() -> getTerrain() -> getY(vectorData.x, vectorData.y) << " " << vectorData.y << std::endl;
    bar -> setPosition(Vector3<f32>(vectorData.x, Map::Instance() -> getTerrain() -> getY(vectorData.x, vectorData.y) + bbOffset, vectorData.y));

    hitBox.moveHitbox(vectorData);
}

//GETTERS
i32 Entity::getID() const{
    return ID;
}

Enumeration::Team Entity::getTeam() const{
    return team;
}

Enumeration::EntityType Entity::getEntityType() const{
    return entityType;
}

Model* Entity::getModel() const{
    return model;
}

Vector2<f32> Entity::getPosition() const{
    return vectorPos;
}

const Box2D& Entity::getHitbox() const{
    return hitBox;
}

i32 Entity::getCurrentHP() const{
    return currentHP;
}

i32 Entity::getMaxHP() const{
    return maxHP;
}

i32 Entity::getViewRadius() const{
    return viewRadius;
}

i32 Entity::getAttackRange() const{
    return attackRange;
}

i32 Entity::getAttackDamage() const{
    return attackDamage;
}

i32 Entity::getAttackSpeed() const{
    return attackSpeed;
}

i32 Entity::getMetalCost() const{
    return metalCost;
}

i32 Entity::getCrystalCost() const{
    return crystalCost;
}

i32 Entity::getHappinessVariation() const{
    return happinessVariation;
}

i32 Entity::getCitizensVariation() const{
    return citizensVariation;
}

Entity* Entity::getTarget() const{
    return target;
}

std::vector<Entity*> Entity::getHostile() const{
    return hostile;
}

void Entity::setBaseColor() {
    model -> setColor(Color(255, 255, 255, 255));
}

void Entity::setDamageColor() {
    model -> setColor(Color(255, 0, 0, 255));
}

/*
    std::string name = "Test";
    std::vector<std::string> * vector = new std::vector<std::string>();
    vector -> push_back(_modelPath);
    std::map< std::string, std::vector < std::string > > * frames = new std::map< std::string, std::vector < std::string > > ();

    frames->insert(std::pair< std::string, std::vector<std::string>>(name, *vector));

    animatedModel = new Animation(_layer, _id, frames);
    animatedModel -> setID(id);

    animatedModel -> setPosition(Vector3<f32>(vectorData.x, Map::Instance() -> getTerrain() -> getY(vectorData.x, vectorData.y), vectorData.y));

void Entity::createBar() {
    bar = new Billboard(Vector3<f32>(getPosition().x, 200, getPosition().y));
}

void Entity::deleteBar() {
    delete bar;
}
	Animation* Entity::getModel() const
	  
	return animatedModel;
*/
