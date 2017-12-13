#include "Unit.h"

Unit::Unit(Vector3<float> *vectorData, bool teamData) : Entity()
{
    //Actions of the units
    this->moving = false;
    this->attacking = false;
    //Default target
    this->target = 0;
    //Position defined by the constructor parameter
    this->position = vectorData;
    //Team defined by the constructor parameter
    this->team = teamData;
    //Defining model position
    this->model->getModel()->setPosition(this->position->getVectorF());
    //unitModel->getModel()->setPosition(irr::core::vector3df(vectorPos->X, vectorPos->Y, vectorPos->Z));
}

Unit::~Unit() {
    delete target;
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
void Unit::setPos(Vector3<float> *vectorData)
{
    this->position = vectorData;
}
void Unit::setDes(Vector3<float> *vectorData)
{
    vectorDes->x = vectorData->x;
    vectorDes->z = vectorData->z;

    float distance, distX, distZ;
    
    distX = vectorData->x - position->x;
    distZ = vectorData->z - position->z;
    distance = sqrt(std::abs(distX) + std::abs(distZ));

    vectorMov->x = (distX / distance) * moveSpeed / 10;
    vectorMov->z = (distZ / distance) * moveSpeed / 10;

    moving = true;
}

Model* Unit::getModel(){
    return this->model;
}