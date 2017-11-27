#include <limits>
#include "nodeGrid.h"
nodeGrid::nodeGrid(int x, int y, irr::scene::ISceneManager *smgrData)
{
    posX = x;
    posY = y;
    visited = false;
    block = false;
    frontier = false;
    weight = std::numeric_limits<int>::max();
    cameFrom = NULL;
    smgr = smgrData;
    cube = smgr->addCubeSceneNode(20.f);
    if(cube){
        cube->setPosition(irr::core::vector3df(x * 20.f, 0, y * 20.f));
        cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        smgr->getMeshManipulator()->setVertexColors(cube->getMesh(), irr::video::SColor(0, 0, 255, 255));
    }
}
nodeGrid::nodeGrid(const nodeGrid& orig){

}
nodeGrid::~nodeGrid(){
    delete cube;
    delete smgr;
}
irr::scene::IMeshSceneNode* nodeGrid::getCube()
{
    return this->cube;
}
void nodeGrid::swapColor(irr::video::SColor colorData){
    smgr->getMeshManipulator()->setVertexColors(cube->getMesh(), colorData);
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
    this->block = blockData;
}
bool nodeGrid::itsVisited()
{
    return visited;
}
void nodeGrid::setVisited(bool visitedData)
{
    this->visited = visitedData;
}
bool nodeGrid::itsFrontier()
{
    return this->frontier;
}
void nodeGrid::setFrontier(bool frontierData)
{
    this->frontier = frontierData;
}
int nodeGrid::getWeight()
{
    return this->weight;
}
void nodeGrid::setWeight(int weightData)
{
    this->weight = weightData;
}
nodeGrid *nodeGrid::getCameFrom()
{
    return this->cameFrom;
}
void nodeGrid::setCameFrom(nodeGrid * last)
{
    this->cameFrom = last;
}
bool nodeGrid::itsCounted()
{
    return this->counted;
}
void nodeGrid::setCounted(bool countedData)
{
    this->counted = countedData;
}
int nodeGrid::getPriority()
{
    return this->priority;
}
void nodeGrid::setPriority(int priorityData)
{
    this->priority = priorityData;
}