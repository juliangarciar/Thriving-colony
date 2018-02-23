#include "Cell.h"
#include <MathEngine/Box2D.h>
#include <MathEngine/Vector2.h>
#include <Building.h>
#include <Unit.h>
Cell::Cell(Vector2<f32>& vectorPosition, i32 idx, i32 halfsize){
    this->position = vectorPosition;
    this->index = idx;
    Vector2<f32> topLeft;
    topLeft.x = vectorPosition.x - halfsize;
    topLeft.y = vectorPosition.y - halfsize;
    Vector2<f32> botRight;
    botRight.x = vectorPosition.x + halfsize;
    botRight.y = vectorPosition.y + halfsize;
    hitBox = Box2D(topLeft, botRight);
    inhabitingBuilding = NULL;
    inhabitingUnits = std::vector<Unit*>();
    neighbors = std::vector<Cell*>();
    blocked = false;
}
Cell::~Cell(){
    inhabitingBuilding = NULL;
    inhabitingUnits.clear();
    neighbors.clear();
}
void Cell::setInhabitingBuilding(Building* buildingPtr){
    inhabitingBuilding = buildingPtr;
}
void Cell::clearInhabitingBuilding(){
    inhabitingBuilding = NULL;
}
void Cell::setInhabitingUnit(Unit* unitPtr){
    inhabitingUnits.push_back(unitPtr);
}
void Cell::clearInhabitingUnit(Unit* unitPtr){
    for(i32 i = 0; i < inhabitingUnits.size(); i++){
        if(inhabitingUnits[i] == unitPtr){
            inhabitingUnits.erase(inhabitingUnits.begin() + i);
            break;
        }
    }
}
void Cell::setNeighbor(Cell* cellPtr){
    neighbors.push_back(cellPtr);
}
void Cell::setBlocked(bool data){
    blocked = data;
}
void Cell::Clear(){
    inhabitingBuilding = NULL;
    inhabitingUnits.clear();
    neighbors.clear();
}
Box2D& Cell::getHitBox(){
    return hitBox;
}
Vector2<f32>& Cell::getPosition(){
    return position;
}
Building* Cell::getInhabitingBuilding(){
    return inhabitingBuilding;
}
std::vector<Unit*> Cell::getInhabitingUnits(){
    return inhabitingUnits;
}
std::vector<Cell*> Cell::getNeighbors(){
    return neighbors;
}
i32 Cell::getIndex(){
    return index;
}
bool Cell::isBlocked(){
    return blocked;
}
bool Cell::collides(Box2D& otherHitbox){
    return hitBox.isOverlappedWith(otherHitbox);
}