#include "Unit.h"

Unit::Unit(irr::core::vector3df *vectorData) : Entity(50)
{
    //moveSpeed = moveSpeedPnt;
    //attackSpeed = attackSpeedPnt;
    //attackDamage = damagePnt;
    //attackRange = attackRangePnt;
    //viewRange = viewRangePnt;
    moveSpeed = 10;
    attackSpeed = 0;
    attackDamage = 0;
    attackRange = 0;
    viewRange = 0;
Unit::Unit(int hitPoints, Vector3<float>* pos, int _moveSpeed, int _attackSpeed, int damage, int attackRadius, int viewRadius, bool _team, Box3D<float>* hitboxPnt, Model* modelPnt) : Entity(hitPoints, pos, _team, hitboxPnt, modelPnt) {
    moveSpeed = _moveSpeed;
    attackSpeed = _attackSpeed;
    attackDamage = damage;
    attackRange = attackRadius;
    viewRange = viewRadius;

    moving = false;
    attacking = false;

    target = 0;

    //smgr = smgrData;
    //cube = smgr->addCubeSceneNode(20.f);
    unitModel = new Model();

    
    vectorDes = new irr::core::vector3df(0, 0, 0);
    vectorPos = new irr::core::vector3df(0, 0, 0);
    vectorMov = new irr::core::vector3df(0, 0, 0);

    vectorPos = vectorData;
    //Irrlicht things to remove (test only)
    //if (cube)
    //{
    //    cube->setPosition(vectorPos->getVectorF());
    //    cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    //    smgr->getMeshManipulator()->setVertexColors(cube->getMesh(), irr::video::SColor(0, 255, 255, 255));
    //}
    unitModel->getModel()->setPosition(irr::core::vector3df(vectorPos->X, vectorPos->Y, vectorPos->Z));
}

Unit::~Unit() {
    delete target;
    //delete smgr;
    //delete cube;
    delete unitModel;
    delete vectorDes;
    delete vectorPos;
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
        if (abs(vectorDes->X - vectorPos->X) < 5.0 && abs(vectorDes->Z - vectorPos->Z) < 5.0)
        {
            moving = false;
            //vectorMov->X = 0;
            //vectorMov->Z = 0;
            //vectorDes->X = 0;
            //vectorDes->Z = 0;
        }
        else
        {
            *vectorPos = unitModel->getModel()->getPosition();
            vectorPos->X += vectorMov->X;
            vectorPos->Z += vectorMov->Z;
            unitModel->getModel()->setPosition(*vectorPos);
            std::cout << "X: " << vectorPos->X << " Y: " << vectorPos->Z << std::endl;
        }
    }
}
void Unit::updateTroop()
{
    moveTroop();
}
void Unit::setPos(irr::core::vector3df *vectorData)
{
    this->vectorPos = vectorData;
}
void Unit::setDes(irr::core::vector3df *vectorData)
{

    vectorDes->X = vectorData->X;
    vectorDes->Z = vectorData->Z;

    float distance, distX, distZ;
    distX = vectorData->X - vectorPos->X;
    distZ = vectorData->Z - vectorPos->Z;
    distance = sqrt(abs(distX) + abs(distZ));

    vectorMov->X = (distX / distance) * moveSpeed;
    vectorMov->Z = (distZ / distance) * moveSpeed;

    moving = true;
}

Model* Unit::getModel(){
    return this->unitModel;
}