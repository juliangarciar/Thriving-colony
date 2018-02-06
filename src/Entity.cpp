#include "Entity.h"

#include "Game.h"

Entity::Entity(SceneNode *layer, int id, const wchar_t *path) {
    ID = id;
    model = new Model(layer, id, path);
    hitbox = new Box3D<float>();
    position = new Vector3<float>();
}

Entity::~Entity() {
    delete position;
    delete hitbox;
    delete model;
}

int Entity::getHP() {
    return hp;
}

/*
* Decreases Hp
* dmg = quantity of hp to drecrease
*/
void Entity::takeDamage(int dmg) {
    hp = hp-dmg;
    tookDamageCountdown = tookDamageTimer;
    // Tint the model red
    setColor(video::SColor(255, 125, 125, 0)); //ToDo: fachada
    if (hp <= 0) {
        hp = 0;
        die();
    }
}

void Entity::die() {
    // ToDo: DEJAR DE DIBUJAR EL MODELO
    // SOLO SE MANDA AL 0,0,0
    
    setPosition(Vector3<float>(0, 0, 0));
    //delete this; 
}

void Entity::returnToOriginalColor() {
    if (!finished && tookDamageCountdown <= 0) {
        setColor(baseColor); //ToDo: sustituir por material
    } else {
        tookDamageCountdown -= Game::Instance() -> getWindow() -> getDeltaTime(); //ToDo: sustituir por timer real
    }
}

void Entity::updateTarget(Entity *newTarget) {
    // target can be null, meaning that he can't attack anything
    target = newTarget;
}

void Entity::setPosition(Vector3<float> vectorData) {
    position -> set(vectorData);
    model -> setPosition(vectorData);
    hitbox -> set(model -> getBoundingBox());
}

void Entity::setHitbox() {
    hitbox -> set(model -> getBoundingBox());
}

void Entity::setColor(irr::video::SColor c){
    //ToDo: reemplazar color por material
    Window::Instance() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(
        model -> getModel() -> getMesh(), c
    );
}

Vector3<float>* Entity::getPosition() {
    return position;
}

Box3D<float>* Entity::getHitbox() {
    return hitbox;
}

Model* Entity::getModel() {
    return model;
}

Enumeration::Team Entity::getTeam() {
    return team;
}

int Entity::getAttackRange() {
    return attackRange;
}

int Entity::getViewRadius() {
    return viewRadius;
}

//ToDo: reemplazar color por material
irr::video::SColor Entity::getColor() {
    return baseColor;
}