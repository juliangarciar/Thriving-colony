#include "Entity.h"
#include "GraphicEngine/Window.h"
#include <MathEngine/Vector3.h>
//#include <MathEngine/Box3D.h>
#include <GraphicEngine/Model.h>
#include <GraphicEngine/SceneNode.h>

Entity::Entity(i32 id, Enumeration::Team t, Enumeration::BreedType b):ID(id), baseColor(255, 0, 0, 0) {
    //ID = id;

    team = t;
    breed = b;

    //baseColor = video::SColor(255, 0, 0, 0); //ToDo: cambiar por material

    tookDamageTimer = 0.1;
    tookDamageCountdown = tookDamageTimer;

    currentHP = 0;
    maxHP = 0;
    viewRadius = 0;
    attackRange = 0;
    metalCost = 0;
    crystalCost = 0;
    happiness = 0;
    citizens = 0;
    cityLevel = 0;

    
    //hitBox = Box2D();
    armyLevel = 0;
}

Entity::~Entity() {
    //delete position;
    //delete hitbox;
    delete model;
    hostile.clear();
}
void Entity::updateTarget(Entity *newTarget) {
    // target can be null, meaning that he can't attack anything
    target = newTarget;
}
void Entity::returnToOriginalColor() {
    if (tookDamageCountdown <= 0.0) {
        setColor(baseColor); //ToDo: sustituir por material
    } else {
        tookDamageCountdown -= Window::Instance() -> getDeltaTime(); //ToDo: sustituir por timer real
    }
}
void Entity::refreshHitbox() {
    hitbox.set(model -> getBoundingBox());
}
//SETTERS
void Entity::takeDamage(i32 dmg) {
    currentHP = currentHP-dmg;
    tookDamageCountdown = tookDamageTimer;
    // Tint the model red
    setColor(video::SColor(255, 125, 125, 0)); //ToDo: sustituir por material
    if (currentHP <= 0) {
        currentHP = 0;
    }
}

void Entity::setModel(SceneNode *layer, const wchar_t *path) {
    model = new Model(layer, ID, path);
    hitbox = Box3D<f32>();
    vectorPos = Vector2<f32>();
    setColor(baseColor);
}
/* Edit */
void Entity::setPosition(Vector2<f32> vectorData) {
    //position -> set(vectorData);
    vectorPos = vectorData;
    model->setPosition(vectorData);
    hitbox.set(model -> getBoundingBox());
    
    /* Create the hitbox in another place */
    Vector2<f32> topLeft;
    Vector2<f32> bottomRight;
    /* Adjust the hitbox properly */
    //topLeft.x = vectorData.x - 120.f;
    //topLeft.y = vectorData.z - 120.f;
    //bottomRight.x = vectorData.x + 120.f;
    //bottomRight.y = vectorData.z + 120.f;
    //hitBox = Box2D(topLeft, bottomRight);
    hitBox.moveHitbox(vectorData.x, vectorData.y);
    //std::cout << "Moving HitBox to: \n";
    //std::cout << hitBox.TopLeft().x << "," << hitBox.TopLeft().y << "\n";
    //std::cout << hitBox.BottomRight().x << "," << hitBox.BottomRight().y << "\n";
}

void Entity::setColor(irr::video::SColor c){
    currentColor = c;
    //ToDo: reemplazar color por material
    Window::Instance() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(
        model -> getModel() -> getMesh(), c
    );
}

void Entity::setID(i32 id){
    ID = id;
    model->setID(id);
}

void Entity::setTarget(Entity* newTarget) {
    target = newTarget;
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

//GETTERS
i32 Entity::getHP() const{
    return currentHP;
}

i32 Entity::getViewRadius() const{
    return viewRadius;
}

i32 Entity::getHappiness() const{
    return happiness;
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

irr::video::SColor Entity::getBaseColor() const{
    return baseColor; //ToDo: reemplazar color por material
}

irr::video::SColor Entity::getCurrentColor() const{
    return currentColor; //ToDo: reemplazar color por material
}

std::vector<Entity*> Entity::getHostile() const{
    return hostile;
}

Vector2<f32> Entity::getPosition() const{
    return vectorPos;
}

Entity* Entity::getTarget() const{
    return target;
}


Box3D<f32> Entity::getHitBox() const{
    return hitbox;
}

Box2D Entity::getHit() const{
    return hitBox;
}

i32 Entity::getAttackRange() const{
    return attackRange;
}

i32 Entity::getArmyLevel() const{
    return armyLevel;
}

i32 Entity::getCellsX() const{
    return kCellsX;
}
i32 Entity::getCellsY() const{
    return kCellsY;
}
















