#include "Unit.h"


Unit::Unit(int id, Vector3<float> vectorData, Enumeration::Team teamData) : Entity(id)
{
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
void Unit::moveTroop()
{
    if (moving)
    {

        if (std::abs(vectorDes->x - position->x) < 5.0 && std::abs(vectorDes->z - position->z) < 5.0)
        {
            moving = false;
        }
        else
        {
            //position = model->getModel()->getPosition();
            position->x += vectorMov->x;
            position->z += vectorMov->z;
            model->getModel()->setPosition(position->getVectorF());
        }
    }
}
void Unit::updateTroop()
{
    moveTroop();
}
void Unit::setPosition(Vector3<float> vectorData)
{
    this->position->set(vectorData);
    this->vectorPos->set(vectorData);
}
void Unit::setDestination(Vector3<float> vectorData)
{
    vectorDes->set(vectorData);

    float distance;

    Vector3<float> desp = *vectorDes - *vectorPos;

    vectorMov->set(desp);
    
    distance = sqrt(std::abs(vectorMov->x) + std::abs(vectorMov->z));

    vectorMov->x = (vectorMov->x / distance) * moveSpeed / 10;
    vectorMov->z = (vectorMov->z / distance) * moveSpeed / 10;

    moving = true;
}

Model* Unit::getModel(){
    return this->model;
}
