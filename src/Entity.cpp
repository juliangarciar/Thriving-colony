#include "Entity.h"
#include "GraphicEngine/Window.h"
#include <MathEngine/Vector3.h>
#include <GraphicEngine/Model.h>
#include <GraphicEngine/SceneNode.h>

Entity::Entity(i32 id, Enumeration::Team t, Enumeration::EntityType e) : ID(id), team(t), entityType(e),
    currentHP(0), maxHP(0), viewRadius(0), attackRange(0), metalCost(0), crystalCost(0), happiness(0), 
    model(nullptr) {
        damageTimer = new Timer(0.1);
        damageTimer -> setCallback([&](){
            //ToDo: cambiar a material original
        });
}

Entity::~Entity() {
    //ToDo: revisar
    if (model != nullptr) delete model;
    hostile.clear();
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
    damageTimer -> restart();
    // Tint the model red
    //ToDo: cambiar a material daño recibido
    if (currentHP <= 0) {
        currentHP = 0;
    }
}

//SETTERS
void Entity::setModel(SceneNode *layer, const wchar_t *path) {
    model = new Model(layer, ID, path);
    hitbox = Box3D<f32>();
    vectorPos = Vector2<f32>();
    //ToDo: cambiar a material normal
}

void Entity::setTarget(Entity *newTarget) {
    // target can be nullptr, meaning that he can't attack anything
    target = newTarget;
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

void Entity::setID(i32 id){
    ID = id;
    model->setID(id);
}

void Entity::setTarget(Entity* newTarget) {
    target = newTarget;
}

//GETTERS
Model* Entity::getModel() const{
    return model;
}

Vector2<f32> Entity::getPosition() const{
    return vectorPos;
}

i32 Entity::getID() const{
    return ID;
}

Enumeration::EntityType Entity::getEntityType() const{
    return entityType;
}

Enumeration::Team Entity::getTeam() const{
    return team;
}

i32 Entity::getHP() const{
    return currentHP;
}

i32 Entity::getViewRadius() const{
    return viewRadius;
}

i32 Entity::getHappiness() const{
    return happiness;
}

std::vector<Entity*> Entity::getHostile() const{
    return hostile;
}

Entity* Entity::getTarget() const{
    return target;
}

//ToDo: revisar
Box3D<f32> Entity::getHitBox() const{
    return hitbox;
}

//ToDo: revisar
Box2D Entity::getHit() const{
    return hitBox;
}

i32 Entity::getCellsX() const{
    return kCellsX;
}
i32 Entity::getCellsY() const{
    return kCellsY;
}
















