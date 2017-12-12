#include <limits>
#include "NodeGrid.h"

nodeGrid::nodeGrid(int x, int y, int z, irr::scene::ISceneManager *smgrData)
{
    posX = x;
    posY = y;
    diag = false;
    block = false;
    frontier = false;
    priority = 0;
    weight = 0;
    cameFrom = NULL;
    counted = false;
    smgr = smgrData;
    cube = smgr -> addCubeSceneNode(20.f);
    diag = false;
    if (cube)
    {
        cube -> setPosition(irr::core::vector3df(x * 20.f, z * 20.f, y * 20.f));
        cube -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        smgr -> getMeshManipulator() -> setVertexColors(cube -> getMesh(), irr::video::SColor(0, 0, 255, 255));
    }
}

nodeGrid::~nodeGrid()
{
    delete cube;
    delete smgr;
}

void nodeGrid::swapColor(irr::video::SColor colorData)
{
    smgr -> getMeshManipulator() -> setVertexColors(cube -> getMesh(), colorData);
}

irr::scene::IMeshSceneNode *nodeGrid::getCube()
{
    return this -> cube;
}


int nodeGrid::getX()
{
    return posX;
}

int nodeGrid::getY()
{
    return posY;
}

bool nodeGrid::itsBlock()
{
    return block;
}

void nodeGrid::setBlock(bool blockData)
{
    this -> block = blockData;
}

void nodeGrid::setDiag(bool diagData)
{
    this -> diag = diagData;
}

bool nodeGrid::itsDiag()
{
    return this -> diag;
}

float nodeGrid::getWeight()
{
    return this -> weight;
}

void nodeGrid::setWeight(float weightData)
{
    this -> weight = weightData;
}

nodeGrid *nodeGrid::getCameFrom()
{
    return this -> cameFrom;
}

void nodeGrid::setCameFrom(nodeGrid *last)
{
    this -> cameFrom = last;
}

bool nodeGrid::itsCounted()
{
    return this -> counted;
}

void nodeGrid::setCounted(bool countedData)
{
    this -> counted = countedData;
}

float nodeGrid::getPriority()
{
    return this -> priority;
}

void nodeGrid::setPriority(float priorityData)
{
    this -> priority = priorityData;
}