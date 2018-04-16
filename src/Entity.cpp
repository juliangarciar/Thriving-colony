#include "Entity.h"
#include "GraphicEngine/Window.h"
#include <MathEngine/Vector3.h>
#include <GraphicEngine/Model.h>
#include <GraphicEngine/SceneNode.h>

Entity::Entity(i32 id, Enumeration::Team t, Enumeration::EntityType e) : ID(id), team(t), entityType(e),
    currentHP(0), maxHP(0), viewRadius(0), attackRange(0), metalCost(0), crystalCost(0), happinessVariation(0), citizensVariation(0),
    model(nullptr), target(nullptr) {
        tookDamageTimer = new Timer(0.1);
        tookDamageTimer -> setCallback([&](){
            //ToDo: cambiar a material original
        });
}

Entity::~Entity() {
    //ToDo: revisar
    if (model != nullptr) delete model;
    hostile.clear();
    delete tookDamageTimer;
}

void Entity::update(){
    tookDamageTimer -> tick();
}

void Entity::refreshHitbox() {
    hitbox.set(model -> getBoundingBox());
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

void Entity::takeDamage(i32 dmg) {
    currentHP = currentHP - dmg;
    tookDamageTimer -> restart();
    // Tint the model red
    //ToDo: cambiar a material daño recibido
    if (currentHP <= 0) {
        currentHP = 0;
    }
}

void Entity::returnToOriginalMaterial() {
    tookDamageTimer -> stop();
    tookDamageTimer -> triggerCallback();
}

//SETTERS
void Entity::setID(i32 id){
    ID = id;
    model -> setID(id);
}

void Entity::setModel(SceneNode *layer, const char *path) {
    model = new Model(layer, ID, path);
    refreshHitbox();
    //ToDo: cambiar a material normal
}

//ToDo: revisar
void Entity::setPosition(Vector2<f32> vectorData) {
    vectorPos = vectorData;
    model -> setPosition(vectorData);

    hitbox.set(model -> getBoundingBox()); //ToDo: revisar si es necesario
    hitBox.moveHitbox(vectorData.x, vectorData.y); //ToDo: revisar si es necesario

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
}

void Entity::setTarget(Entity *newTarget) {
    target = newTarget;
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

//ToDo: revisar
//Box3D<f32> Entity::getHitBox() const{
//    return hitbox;
//}

//ToDo: revisar
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