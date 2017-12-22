#include "Entity.h"

Entity::Entity(int id) {
    this->ID = id;
    //ToDo: hacer aumento de felicidad, tropas nivel y tal
    model = new Model(id);
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
    if (hp <= 0) {
        hp = 0;
        die();
    }
}

void Entity::die() {
    delete this; 
}

void Entity::setPosition(Vector3<float> vectorData){
    this->position->set(vectorData);
    this->model->setPosition(vectorData);
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