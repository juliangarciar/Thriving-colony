#include "Unit.h"

Unit::Unit(int hpPnt, int moveSpeedPnt, int attackSpeedPnt, int damagePnt, int attackRangePnt, int viewRangePnt, int xData, int yData, int zData, irr::scene::ISceneManager *smgrData) : Entity(hpPnt)
{
    moveSpeed = moveSpeedPnt;
    attackSpeed = attackSpeedPnt;
    attackDamage = damagePnt;
    attackRange = attackRangePnt;
    viewRange = viewRangePnt;

    moving = false;
    attacking = false;

    target = 0;

    smgr = smgrData;
    cube = smgr->addCubeSceneNode(20.f);
    vectorDes = new irr::core::vector3df(0, 20.f, 0);
    vectorPos = new irr::core::vector3df(0, 20.f, 0);
    vectorMov = new irr::core::vector3df(0, 20.f, 0);
    if (cube)
    {
        cube->setPosition(irr::core::vector3df(xData * 20.f, yData * 20.f, zData * 20.f));
        cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        smgr->getMeshManipulator()->setVertexColors(cube->getMesh(), irr::video::SColor(0, 255, 255, 255));
    }
}

Unit::~Unit() {
    delete target;
    delete smgr;
    delete cube;
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
            *vectorPos = cube->getPosition();
            vectorPos->X += vectorMov->X;
            vectorPos->Z += vectorMov->Z;
            cube->setPosition(*vectorPos);
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
void Unit::setDes(irr::core::vector3df vectorData)
{

    vectorDes->X = vectorData.X;
    vectorDes->Z = vectorData.Z;

    float distance, distX, distZ;
    distX = vectorData.X - vectorPos->X;
    distZ = vectorData.Z - vectorPos->Z;
    distance = sqrt(abs(distX) + abs(distZ));

    vectorMov->X = (distX / distance) * moveSpeed;
    vectorMov->Z = (distZ / distance) * moveSpeed;

    moving = true;
}