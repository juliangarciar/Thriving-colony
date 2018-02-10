#include <limits>
#include "nodeGrid.h"
nodeGrid::nodeGrid(i32 x, i32 y, i32 z, irr::scene::ISceneManager *smgrData)
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
    if(cube){
        cube -> setPosition(irr::core::vector3df(x * 20.f, z * 20.f, y * 20.f));
        cube -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        smgr -> getMeshManipulator() -> setVertexColors(cube -> getMesh(), irr::video::SColor(0, 0, 255, 255));
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
    return this -> cube;
}
void nodeGrid::swapColor(irr::video::SColor colorData){
    smgr -> getMeshManipulator() -> setVertexColors(cube -> getMesh(), colorData);
}

i32 nodeGrid::getX()
{
    return posX;
}
i32 nodeGrid::getY()
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
void nodeGrid::setDiag(bool diagData){
    this -> diag = diagData;
}
bool nodeGrid::itsDiag(){
    return this -> diag;
}
bool nodeGrid::itsFrontier()
{
    return this -> frontier;
}
void nodeGrid::setFrontier(bool frontierData)
{
    this -> frontier = frontierData;
}
f32 nodeGrid::getWeight()
{
    return this -> weight;
}
void nodeGrid::setWeight(f32 weightData)
{
    this -> weight = weightData;
}
nodeGrid *nodeGrid::getCameFrom()
{
    return this -> cameFrom;
}
void nodeGrid::setCameFrom(nodeGrid * last)
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
f32 nodeGrid::getPriority()
{
    return this -> priority;
}
void nodeGrid::setPriority(f32 priorityData)
{
    this -> priority = priorityData;
}