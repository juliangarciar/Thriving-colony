#include "Unit.h"
#include "Game.h"

Unit::Unit(int id, SceneNode *layer, Vector3<float> vectorData, Enumeration::Team teamData) : Entity(layer, id) {
    //Actions of the units
    this->moving = false;
    this->attacking = false;
    //Default target
    this->target = 0;
    //Position defined by the constructor parameter
    this->vectorPos = new Vector3<float>();
    this->vectorDes = new Vector3<float>();
    this->vectorMov = new Vector3<float>();
    //Team defined by the constructor parameter
    this->team = teamData;
    //Defining model position
    this->model->getModel()->setPosition(vectorData.getVectorF());
    //unitModel->getModel()->setPosition(irr::core::vector3df(vectorPos->X, vectorPos->Y, vectorPos->Z));
}

Unit::~Unit() {
    delete target;
    delete vectorPos;
    delete vectorDes;
    delete vectorMov;
}

void Unit::attack() {
    if (target != 0) {
        target -> takeDamage(attackDamage);
    }
}

Entity* Unit::getTarget() {
    return target;
}

void Unit::setMoving(bool movingPnt) {
    moving = movingPnt;
}

void Unit::setAttacking(bool attackingPnt) {
    attacking = attackingPnt;
}
void Unit::moveTroop() {
    if (moving) {
        if (std::abs(vectorDes->x - position->x) < 5.0 && std::abs(vectorDes->z - position->z) < 5.0) {
            moving = false;
        } else {
            this->setTroopPosition(*vectorPos + *vectorMov);
        }
    }
}

void Unit::updateTroop() {
    moveTroop();
}

void Unit::setTroopPosition(Vector3<float> vectorData) {
    this->vectorPos->set(vectorData);
    this->setPosition(vectorData);
}

void Unit::setTroopDestination(Vector3<float> vectorData) {
    vectorDes->set(vectorData);

    Vector3<float> desp = *vectorDes - *vectorPos;

    float distance = std::abs(std::sqrt(std::pow(desp.x, 2) + std::pow(desp.z, 2)));

    vectorMov->x = (desp.x / distance) * moveSpeed * Game::Instance()->getWindow()->getDeltaTime();
    vectorMov->z = (desp.z / distance) * moveSpeed * Game::Instance()->getWindow()->getDeltaTime();

    moving = true;
}

Model* Unit::getModel() {
    return this->model;
}

/*
void Unit::assignBattle(Battle* _battle) {
    battleInvolved = _battle;
}

void Unit::updateTarget() {
    if (battleInvolved != NULL) {
        //ToDo: definir como va a ser lo del equipo porque cada uno dice una cosa y ayer se iba a decidir y no se decidio
        //      por ahora esta que siempre es humano 
        target = battleInvolved -> getClosestTarget(*position, Enumeration::Team::Human);
    }
}*/