#include "Entity.h"
#include "Map.h"
#include <MathEngine/Vector3.h>
#include <GraphicEngine/Model.h>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Window.h>

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
    std::string _texturePath) : 
        layer(_layer),
        ID(_id),
        team(_team),
        entityType(_type),
        model(nullptr),
        vectorPos(0,0),
        hitBox(Vector2<f32>(0, 0),
               Vector2<f32>(_cellsY * cSize,
                            _cellsX * cSize)),
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
        hostile(),
        kCellsX(_cellsX),
        kCellsY(_cellsY) 
{
    //set Timer
    tookDamageTimer = new Timer(0.1);
    tookDamageTimer -> setCallback([&](){
        setBaseMaterial();
    });

    //Set model
    model = new Model(_layer, _id, _modelPath);
    
    //Set texture
    //model->setMaterial(new Material(new Texture(_texturePath.c_str())));

    /* Box2D parameters */
    Vector2<f32> topLeft;
    Vector2<f32> bottomRight;

    /* Set the 2D hitbox params */
    //topLeft.x = (kCellsX / 2.0) * (-80.f) + 1;
    //topLeft.y = (kCellsY / 2.0) * (-80.f) + 1;
    //bottomRight.x = (kCellsX / 2.0) * (80.f) - 1;
    //bottomRight.y = (kCellsY / 2.0) * (80.f) - 1;

    /* Set the 2D hitbox */
    //hitBox = Box2D(topLeft, bottomRight); 
}

//ToDo: revisar
Entity::~Entity() {
    if (model != nullptr) delete model;
    hostile.clear();
    delete tookDamageTimer;
}

void Entity::update(){
    tookDamageTimer -> tick();
}

void Entity::addHostile(Entity* newHostileUnit) {
    hostile.push_back(newHostileUnit);
}

void Entity::removeHostile(Entity* oldHostileUnit) {
    bool done = false;
    for (i32 i = 0; i < hostile.size() && done == false; i++) {
        if (hostile.at(i) == oldHostileUnit) {
            hostile.erase(hostile.begin() + i);
            done = true;
        }
    }
}

void Entity::putHostileTargetsToNull() {
    for (i32 i = 0; i < hostile.size(); i++) {
        hostile.at(i) -> setTarget(nullptr);
    }
}

//void Entity::takeDamage(i32 dmg) {
//    currentHP = currentHP - dmg;
//    tookDamageTimer -> restart();
//    // Tint the model red
//    //ToDo: cambiar a material daño recibido
//    if (currentHP <= 0) {
//        currentHP = 0;
//    }
//}

//SETTERS
void Entity::setID(i32 id){
    ID = id;
    model -> setID(id);
}

void Entity::setPosition(Vector2<f32> vectorData) {
    vectorPos = vectorData;

    model -> setPosition(Vector3<f32>(vectorData.x, Map::Instance() -> getTerrain() -> getY(vectorData.x, vectorData.y), vectorData.y));

    hitBox.moveHitbox(vectorData);
    //std::cout << "Hitbox: " << hitBox.TopLeft().x << "," << hitBox.TopLeft().y << " y " << hitBox.BottomRight().x << "," << hitBox.BottomRight().y << "\n";
}

void Entity::setTarget(Entity *newTarget) {
    target = newTarget;
}

//GETTERS
SceneNode *Entity::getLayer() {
    return layer;
}

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

Box2D Entity::getHitbox() const{
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

i32 Entity::getCellsX() const{
    return kCellsX;
}

i32 Entity::getCellsY() const{
    return kCellsY;
}

//ToDo: anadido por rafa
void Entity::setBaseMaterial() {
    model -> setMaterial(baseMat);
}

void Entity::setDamagedMaterial() {
    model -> setMaterial(damagedMat);
}

    //position -> set(vectorData);
    /* Adjust the hitbox properly */
    //Vector2<f32> topLeft;
    //Vector2<f32> bottomRight;
    //topLeft.x = vectorData.x - 120.f;
    //topLeft.y = vectorData.z - 120.f;
    //bottomRight.x = vectorData.x + 120.f;
    //bottomRight.y = vectorData.z + 120.f;
    //hitBox = Box2D(topLeft, bottomRight);
    //std::cout << "Moving HitBox to: \n";
    //std::cout << hitBox.TopLeft().x << "," << hitBox.TopLeft().y << "\n";
    //std::cout << hitBox.BottomRight().x << "," << hitBox.BottomRight().y << "\n";