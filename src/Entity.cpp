#include "Entity.h"

#include "Game.h"

Entity::Entity(SceneNode *layer, int id, const wchar_t *path) {
    this -> ID = id;
    //ToDo: hacer aumento de felicidad, tropas nivel y tal
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
    // Tint the model red
    tookDamageCountdown = tookDamageTimer;
    Window::Instance() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(model -> getModel() -> getMesh(), video::SColor(255, 125, 125, 0));
    if (hp <= 0) {
        hp = 0;
        die();
    }
}

void Entity::die() {
    //ToDo: DEJAR DE DIBUJAR CUBOS
    // SOLO SE MANDAN AL 0,0,0
    //
    //
    //
    
    this -> setPosition(Vector3<float>(0, 0, 0));
    //delete this; 
}

void Entity::changeRedTint() {
    if (!finished && tookDamageCountdown <= 0) {
        Window::Instance() -> getSceneManager() -> getMeshManipulator() -> setVertexColors(model -> getModel() -> getMesh(), baseColor); //ToDo fachada
    } else {
        tookDamageCountdown -= Game::Instance() -> getWindow() -> getDeltaTime();
    }
}

void Entity::setPosition(Vector3<float> vectorData) {
    this -> position -> set(vectorData);
    this -> model -> setPosition(vectorData);
    this -> hitbox -> set(model -> getBoundingBox());
}

void Entity::setHitbox() {
    this -> hitbox -> set(model -> getBoundingBox());
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

void Entity::updateTarget(Entity *newTarget) {
    // target can be null, meaning that he cant attack anything
    target = newTarget;
}

int Entity::getAttackRange() {
    return attackRange;
}

int Entity::getViewRadius() {
    return viewRadius;
}