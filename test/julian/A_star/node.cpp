#include <limits>
#include "node.h"
node::node(i32 x, i32 y){
    posX = x;
    posY = y;
    visited = false;
    block = false;
    frontier = false;
    weight = std::numeric_limits<i32>::max();
    //weight = 0;
    cameFrom = NULL;
    rectangle = new sf::RectangleShape(sf::Vector2f(20.f, 20.f));
    rectangle -> setFillColor(sf::Color::Green);
    rectangle -> setOrigin(sf::Vector2f(0, 0));
    rectangle -> setPosition(sf::Vector2f(x * 24.f, y * 24.f));

}
node::node(const node& orig){

}
node::~node(){
    delete rectangle;
}
void node::swapColor(sf::Color color)
{
    rectangle -> setFillColor(color);
}
sf::RectangleShape *node::getRectangle(){
    return rectangle;
}
i32 node::getX(){
    return posX;
}
i32 node::getY(){
    return posY;
}
bool node::itsBlock(){
    return block;
}
void node::setBlock(bool blockData){
    this -> block = blockData;
}
bool node::itsVisited(){
    return visited;
}
void node::setVisited(bool visitedData){
    this -> visited = visitedData;
}
bool node::itsFrontier(){
    return this -> frontier;
}
void node::setFrontier(bool frontierData){
    this -> frontier = frontierData;
}
i32 node::getWeight()
{
    return this -> weight;
}
void node::setWeight(i32 weightData){
    this -> weight = weightData;
}
node* node::getCameFrom(){
    return this -> cameFrom;
}
void node::setCameFrom(node* last){
    this -> cameFrom = last;
}
bool node::itsCounted(){
    return this -> counted;
}
void node::setCounted(bool countedData){
    this -> counted = countedData;
}
i32 node::getPriority(){
    return this -> priority;
}
void node::setPriority(i32 priorityData){
    this -> priority = priorityData;
}