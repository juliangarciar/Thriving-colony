#include "Entity.h"
#include "Game.h"

Entity::Entity(i32 id, Enumeration::Team t, Enumeration::BreedType b) {
    ID = id;

    team = t;
    breed = b;

    baseColor = video::SColor(255, 0, 0, 0); //ToDo: cambiar por material

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
    armyLevel = 0;
}

Entity::~Entity() {
    delete position;
    delete hitbox;
    delete model;
    hostile.clear();
}

//METHODS
void Entity::takeDamage(i32 dmg) {
    currentHP = currentHP-dmg;
    tookDamageCountdown = tookDamageTimer;
    // Tint the model red
    setColor(video::SColor(255, 125, 125, 0)); //ToDo: sustituir por material
    if (currentHP <= 0) {
        currentHP = 0;
    }
}

void Entity::updateTarget(Entity *newTarget) {
    // target can be null, meaning that he can't attack anything
    target = newTarget;
}

void Entity::refreshHitbox() {
    hitbox -> set(model -> getBoundingBox());
}

void Entity::returnToOriginalColor() {
    if (tookDamageCountdown <= 0.0) {
        setColor(baseColor); //ToDo: sustituir por material
    } else {
        tookDamageCountdown -= Window::Instance() -> getDeltaTime(); //ToDo: sustituir por timer real
    }
}

//SETTERS
void Entity::setModel(SceneNode *layer, const wchar_t *path) {
    model = new Model(layer, ID, path);
    hitbox = new Box3D<f32>();
    position = new Vector3<f32>();
    setColor(baseColor);
}

void Entity::setPosition(Vector3<f32> vectorData) {
    position -> set(vectorData);
    model -> setPosition(vectorData);
    hitbox -> set(model -> getBoundingBox());
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

//GETTERS
Vector3<f32>* Entity::getPosition() {
    return position;
}

Box3D<f32>* Entity::getHitbox() {
    return hitbox;
}

Model* Entity::getModel() {
    return model;
}

Enumeration::Team Entity::getTeam() {
    return team;
}

i32 Entity::getAttackRange() {
    return attackRange;
}

i32 Entity::getViewRadius() {
    return viewRadius;
}

Enumeration::EntityType Entity::getEntityType() {
    return entityType;
}

i32 Entity::getHP() {
    return currentHP;
}

i32 Entity::getID() {
    return ID;
}

i32 Entity::getHappiness() {
    return happiness;
}

irr::video::SColor Entity::getBaseColor() {
    return baseColor; //ToDo: reemplazar color por material
}

irr::video::SColor Entity::getCurrentColor() {
    return currentColor; //ToDo: reemplazar color por material
}
i32 Entity::getCells(){
    return kCells;
}

i32 Entity::getArmyLevel() {
    return armyLevel;
}

std::vector<Entity*> Entity::getHostile() {
    return hostile;
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

void Entity::setTarget(Entity* newTarget) {
    target = newTarget;
}

Entity* Entity::getTarget() {
    return target;
}

void Entity::putHostileTargetsToNull() {
    for (i32 i = 0; i < hostile.size(); i++) {
        hostile.at(i) -> setTarget(NULL);
    }
}