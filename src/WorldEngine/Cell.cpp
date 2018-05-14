#include "Cell.h"
#include <MathEngine/Box2D.h>
#include <MathEngine/Vector2.h>
#include <Building.h>
#include <Unit.h>
Cell::Cell(Vector2<f32> vectorPosition, const Box2D& hitboxData, i32 idx):position(vectorPosition),
                                                                          hitBox(hitboxData),
                                                                          index(idx),
                                                                          inhabitingBuilding(nullptr),
                                                                          inhabitingUnits(),
                                                                          neighbors(),
                                                                          blocked(false){}

Cell::~Cell(){
    inhabitingBuilding = nullptr;
    inhabitingUnits.clear();
    neighbors.clear();
}
void Cell::setInhabitingBuilding(Building* buildingPtr){
    if(inhabitingBuilding == nullptr){
        inhabitingBuilding = buildingPtr;
        blocked = true;
    }
}
void Cell::clearInhabitingBuilding(){
    if(inhabitingBuilding != nullptr){
        inhabitingBuilding = nullptr;
        blocked = false;
    }
}
void Cell::setInhabitingUnit(Unit* unitPtr){
    inhabitingUnits.push_back(unitPtr);
}
void Cell::clearInhabitingUnit(Unit* unitPtr){
    for(std::size_t i = 0; i < inhabitingUnits.size(); i++){
        if(inhabitingUnits[i] == unitPtr){
            inhabitingUnits[i] == nullptr;
            //inhabitingUnits.erase(inhabitingUnits.begin() + i);
            return;
        }
    }
    //if(inhabitingUnits.size() == 0){
    //    blocked = false;
    //}
}
void Cell::setNeighbor(Cell* cellPtr){
    neighbors.push_back(cellPtr);
}
void Cell::setBlocked(bool data){
    blocked = data;
}
void Cell::Clear(){
    inhabitingBuilding = nullptr;
    inhabitingUnits.clear();
    neighbors.clear();
}
const Box2D& Cell::getHitbox() const{
    return hitBox;
}
Vector2<f32> Cell::getPosition() const{
    return position;
}
Building* Cell::getInhabitingBuilding() const{
    return inhabitingBuilding;
}
const std::vector<Unit*>& Cell::getInhabitingUnits(){
    for(std::size_t i = 0; i < inhabitingUnits.size(); i++){
        if(inhabitingUnits[i] == nullptr){
            inhabitingUnits.erase(inhabitingUnits.begin() + i);
        }
    }
    return inhabitingUnits;
}
const std::vector<Cell*>& Cell::getNeighbors() const{
    return neighbors;
}
i32 Cell::getIndex() const{
    return index;
}
bool Cell::isBlocked() const{
    return blocked;
}
bool Cell::collides(const Box2D& otherHitbox) const{
    return hitBox.isOverlappedWith(otherHitbox);
}