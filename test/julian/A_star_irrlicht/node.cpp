#include <limits>
#include "node.h"
node::node(i32 x, i32 y, irr::scene::ISceneManager *smgrData)
{
    posX = x;
    posY = y;
    visited = false;
    block = false;
    frontier = false;
    weight = std::numeric_limits<i32>::max();
    cameFrom = NULL;
    smgr = smgrData;
    cube = smgr -> addCubeSceneNode(20.f);
    if(cube){
        cube -> setPosition(irr::core::vector3df(x * 20.f, 0, y * 20.f));
        cube -> setMaterialFlag(irr::video::EMF_LIGHTING, false);
        smgr -> getMeshManipulator() -> setVertexColors(cube -> getMesh(), irr::video::SColor(0, 0, 255, 255));
    }
}
node::node(const node& orig){

}
node::~node(){
    delete cube;
    //delete smgr;
}
irr::scene::IMeshSceneNode* node::getCube()
{
    return this -> cube;
}
void node::swapColor(irr::video::SColor colorData){
    smgr -> getMeshManipulator() -> setVertexColors(cube -> getMesh(), colorData);
}

i32 node::getX()
{
    return posX;
}
i32 node::getY()
{
    return posY;
}
bool node::itsBlock()
{
    return block;
}
void node::setBlock(bool blockData)
{
    this -> block = blockData;
}
bool node::itsVisited()
{
    return visited;
}
void node::setVisited(bool visitedData)
{
    this -> visited = visitedData;
}
bool node::itsFrontier()
{
    return this -> frontier;
}
void node::setFrontier(bool frontierData)
{
    this -> frontier = frontierData;
}
i32 node::getWeight()
{
    return this -> weight;
}
void node::setWeight(i32 weightData)
{
    this -> weight = weightData;
}
node *node::getCameFrom()
{
    return this -> cameFrom;
}
void node::setCameFrom(node * last)
{
    this -> cameFrom = last;
}
bool node::itsCounted()
{
    return this -> counted;
}
void node::setCounted(bool countedData)
{
    this -> counted = countedData;
}
i32 node::getPriority()
{
    return this -> priority;
}
void node::setPriority(i32 priorityData)
{
    this -> priority = priorityData;
}