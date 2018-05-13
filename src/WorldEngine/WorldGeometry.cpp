#include "WorldGeometry.h"
#include "Cell.h"
#include "Quadtree.h"
#include <MathEngine/Vector2.h>
#include <Map.h>
#include <MathEngine/Box2D.h>
#include <Building.h>
#include <Unit.h>
#include <priorityqueue/PriorityQueue.h>
#include <cstdlib> 

WorldGeometry* WorldGeometry::pinstance = 0;
WorldGeometry* WorldGeometry::Instance(){
    if(pinstance == 0){
        pinstance = new WorldGeometry();
    }
    return pinstance;
}
WorldGeometry::WorldGeometry():quadTree(nullptr), maxGameUnits(10){

}
WorldGeometry::~WorldGeometry(){
    mCells.clear();
    cellsDistance.clear();
    delete quadTree;
}
void WorldGeometry::Init(i32 _cellSize, i32 _mapX, i32 _mapY, i32 _quadDepth){
/* Calculates the maximun N cells and reserve memory */
    cellSize = _cellSize;
    mapAxis = Vector2<i32>(_mapX, _mapY);
    mapArea = mapAxis.x * mapAxis.y;
    maxCellsX = mapAxis.x / cellSize;
    maxCellsY = mapAxis.y / cellSize;
    maxCells = maxCellsX * maxCellsY;
    mCells = std::vector< Cell* >(maxCells);
    cellsDistance = std::vector< std::vector<f32> >(maxCells);
    quadTree = nullptr;
    squadPosition = std::vector< std::vector< Vector2<f32> > >(maxGameUnits);
    f32 gradesPerUnit;
    const f32 radious = cellSize / 2;

    for(i32 i = 0; i < maxGameUnits; i++){
        squadPosition[i] = std::vector< Vector2<f32> >(i + 1);
        for(std::size_t j = 0; j < squadPosition[i].size(); j++){
            if(squadPosition[i].size() == 1)
                squadPosition[i][j] = Vector2<f32>(0, 0);
            else
                gradesPerUnit = (360 / squadPosition[i].size()) * j * (PI / 180.0f);
            
            squadPosition[i][j] = Vector2<f32>(radious * std::cos(gradesPerUnit), radious * std::sin(gradesPerUnit)); 
        }
    }
/* Especifies the N cells each axis has */    
    for (i32 y = 0; y < maxCellsY; y++)
    {
        for (i32 x = 0; x < maxCellsX; x++)
        {
        /* Calculates the index */
            i32 index = y * maxCellsX + x;
        /* Especifies the center where the cell is allocated */
            f32 dX = x * cellSize + cellSize / 2;
            f32 dY = y * cellSize + cellSize / 2;
            Vector2<f32> tmp = Vector2<f32>(dX, dY);
        /* Creates the hitbox */
            Vector2<f32> topLeft;
            topLeft.x = tmp.x - cellSize / 2;
            topLeft.y = tmp.y - cellSize / 2;
            Vector2<f32> botRight;
            botRight.x = tmp.x + cellSize / 2;
            botRight.y = tmp.y + cellSize / 2;
            Box2D hitBox = Box2D(topLeft, botRight);
        /* Creates the cell, and copy it to the WorldGeometry vector */
            Cell* cell = new Cell(tmp, hitBox, index);
            //mCells.push_back(cell);
            mCells[index] = cell;
        }
    }
/* Creates the hitbox for the Quadtree, and creates it */
    Vector2<f32> topLeft(0, 0);
    Vector2<f32> botRight(mapAxis.x, mapAxis.y);
    Box2D hitBox(topLeft, botRight);
    Vector2<f32> center(botRight / 2);
    quadTree = new Quadtree(center, hitBox, 1);
/* Adds each cell in the quadtree */
    for(i32 i = 0; i < maxCells; i++){
        quadTree->insertCell(mCells[i]);
    }
/* Calculate neighbors for each cell (this method cost a lot of time) */
    //for(i32 i = 0; i < mCells.size(); i++){
    //    quadTree->assignNeighbors(mCells[i]);
    //}
/* Calculate neighbors for each cell (faster version) */
    for(i32 y = 0; y < maxCellsY; y++){
        for(i32 x = 0; x < maxCellsX; x++){
            Cell* tmp = mCells.at(maxCellsY * y + x);
            if(y == 0){
                if(x == 0){
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNeighbor(mCells.at(maxCellsX));
                    tmp->setNeighbor(mCells.at(maxCellsX + 1));
                }
                else if(x == maxCellsX - 1){
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(2 * tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(2 * tmp->getIndex()));
                }
                else{
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNeighbor(mCells.at(2 * tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(2 * tmp->getIndex()));
                    tmp->setNeighbor(mCells.at(2 * tmp->getIndex() + 1));
                }
            }
            else if(y == maxCellsY - 1){
                if(x == 0){
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX + 1));
                }
                else if(x == maxCellsX - 1){
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX - 1));
                }
                else{
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX + 1));
                }
            }
            else{
                if(x == 0){
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX + 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCellsX));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCellsX + 1));
                }
                else if(x == maxCellsX - 1){
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCellsX - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCellsX));
                }
                else{
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - maxCellsX + 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCellsX - 1));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCellsX));
                    tmp->setNeighbor(mCells.at(tmp->getIndex() + maxCellsX + 1));
                }
            }
        }
    }
/* Pre-calculate the distance between each cell and his neighbors */
    for(i32 j = 0; j < maxCells; j++){
        std::vector<Cell*> neighbors = mCells[j]->getNeighbors();
        i32 size = neighbors.size();
        cellsDistance[j] = std::vector<f32>(size);
        for(i32 k = 0; k < size; k++){
            cellsDistance[j][k] = calculateDistance(mCells[j]->getPosition(), neighbors[k]->getPosition());
            /* Debug intended */
            //if(cellsDistance[j][k] == 0){
            //    std::cout << "Weird stuff happens at init at: " << j << "," << k << "\n";
            //}
        }
    }
    
}
void WorldGeometry::Clear(){
    mCells.clear();
    cellsDistance.clear();
    delete quadTree;
}
void WorldGeometry::build(Building* buildingPtr){
    quadTree->insertBuilding(buildingPtr);
}
void WorldGeometry::updateUnitCell(Vector2<f32> oldPosition, Vector2<f32> newPosition, Unit* unitPtr){
    Cell* oldCell = positionToCell(oldPosition);
    Cell* newCell = positionToCell(newPosition);
    if(oldCell != newCell){
        oldCell->clearInhabitingUnit(unitPtr);
        newCell->setInhabitingUnit(unitPtr);
    }
}
void WorldGeometry::clearUnitCell(Vector2<f32> positionVector, Unit* unitPtr){
    positionToCell(positionVector)->clearInhabitingUnit(unitPtr);
}
void WorldGeometry::setUnitCell(Vector2<f32> positionVector, Unit* unitPtr){
    positionToCell(positionVector)->setInhabitingUnit(unitPtr);
}
bool WorldGeometry::checkBuildingSpace(Building* buildingPtr){
    Box2D dummy = buildingPtr->getHitbox().getAmplifiedBox(79.f);
    return quadTree->canBuild(dummy);
}
Vector2<f32> WorldGeometry::correctBuildingPosition(Vector2<f32> targetPos, Building *buildingPtr){
    Vector2<f32> correctOne = Vector2<f32>();
    if(buildingPtr != nullptr){
        Cell* dummy = positionToCell(targetPos);
        Vector2<f32> storage;
        /* Change this method */
        if(buildingPtr -> getCellsX() % 2 == 0){
            storage = dummy->getHitbox().TopLeft();
            correctOne.x = storage.x;
            correctOne.y = storage.y;
            storage.x -= cellSize / 2;
            storage.y -= cellSize / 2;
            storage.x -= (buildingPtr -> getCellsX() / 2) * (cellSize / 2);
            storage.y -= (buildingPtr -> getCellsY() / 2) * (cellSize / 2);
        }
        else{
            storage = dummy->getHitbox().Center();
            correctOne.x = storage.x;
            correctOne.y = storage.y;
            storage.x -= (buildingPtr -> getCellsX() - 1) * (cellSize / 2);
            storage.y -= (buildingPtr -> getCellsY() - 1) * (cellSize / 2);
        }
    }
    return correctOne;
}
/* !! */
/* NEEDS A HARD CLEAN !!! */
Cell* WorldGeometry::getValidCell(Cell* referenceTarget, Cell* referenceOrigin, Building* buildingPtr){
    /* The wanted Cell */
    Cell* validCell = nullptr;
    /* Intended swap */
    Cell* sourceCell = referenceTarget;
    Cell* targetCell = referenceOrigin;
    i32 sourceIndex = sourceCell->getIndex();
    //i32 targetIndex = targetCell->getIndex();
    /* Check what's needed and what's not */
    std::vector<f32> GCosts = std::vector<f32>(maxCells, 0);
    std::vector<f32> FCosts = std::vector<f32>(maxCells, 0);

    std::vector< Cell* > shortestPath = std::vector<Cell*>(maxCells, nullptr);
    std::vector< Cell* > searchFrontier = std::vector<Cell*>(maxCells, nullptr);
    /* Priority queue, that orders the weights of each iterated Cell */
    IndexedPriorityQLow<float> pq(FCosts, maxCells);
    pq.insert(sourceIndex);
    /* Algorithm start */ 
    while(!pq.empty()){
        i32 closestIndex = pq.Pop();
    /* Adds the cell to the path vector */
        shortestPath[closestIndex] = searchFrontier[closestIndex];
    /* Stop condition, research about a system of conditions */
        if(buildingPtr != nullptr){
            Vector2<f32> tmp = indexToCell(closestIndex)->getPosition();
            //Vector3<f32> dummy;
            //dummy.x = tmp.x;
            //dummy.z = tmp.y;
            //dummy.y = Map::Instance() -> getTerrain() -> getY(dummy.x, dummy.z);
            buildingPtr->setPosition(tmp);
            if(!checkBuildingSpace(buildingPtr)){
                validCell = indexToCell(closestIndex);
                return validCell;
            }
        }
        else if(!indexToCell(closestIndex)->isBlocked()){
            validCell = indexToCell(closestIndex);
            return validCell; 
        }
    /* Get neighbors of the chosen cell */
        std::vector<Cell*> neighbors = getNeighbors(closestIndex);
    /* Calculate the cost for each neighbor to the targetCell */
        for(i32 i = 0; i < neighbors.size(); i++){
            i32 potentialNode = neighbors[i]->getIndex();
            f32 HCost = calculateDistance(neighbors[i]->getPosition(), targetCell->getPosition());
            f32 GCost = GCosts[closestIndex] + getCost(closestIndex, i);
            //std::cout << "Distancia H: " << HCost << "\n";
            //std::cout << "Distancia G: " << GCost << "\n";
            if(searchFrontier[potentialNode] == nullptr){
                FCosts[potentialNode] = GCost + HCost;
                GCosts[potentialNode] = GCost;

                pq.insert(potentialNode);
                searchFrontier[potentialNode] = indexToCell(closestIndex);
            }
        /* Fix this method, isn't working properly */
            else if((GCost < GCosts[potentialNode]) && (shortestPath[potentialNode] == nullptr)){
                FCosts[potentialNode] = GCost + HCost;
                GCosts[potentialNode] = GCost;

                searchFrontier[potentialNode] = indexToCell(closestIndex);
            }    
        }
    }
    return validCell;
}
Cell* WorldGeometry::positionToCell(Vector2<f32> position) const{
    i32 idx = (i32)((maxCellsX) * position.x / mapAxis.x) + 
                ((i32)((maxCellsY) * position.y / mapAxis.y) * maxCellsX);

    if(idx < 0 || idx > mCells.size()){
        return nullptr;
    }
    if (idx >= maxCells){
        idx = maxCells - 1;
    }
    
    Cell* tmp = mCells.at(idx); 
    
    return tmp;
}
Cell* WorldGeometry::indexToCell(i32 index){
    return mCells[index];
}
f32 WorldGeometry::calculateDistance(Vector2<f32> a, Vector2<f32> b){
    f32 dX = b.x - a.x;
    f32 dY = b.y - a.y;
    return std::sqrt(std::pow(dX, 2) + std::pow(dY,2));
}
f32 WorldGeometry::getCost(i32 indexA, i32 indexB){
    if(cellsDistance[indexA][indexB] == 0)
        std::cout << "Weird stuff happens \n";
    return cellsDistance[indexA][indexB];
}
std::vector< Unit* > WorldGeometry::getNeighborUnits(Vector2<f32> positionVector){
    std::vector< Unit* > neighborUnits;
    std::vector< Cell* > neighborCells = positionToCell(positionVector)->getNeighbors();
    neighborCells.push_back(positionToCell(positionVector));
    for(size_t i = 0; i < neighborCells.size(); i++){
        if(!neighborCells[i]->getInhabitingUnits().empty()){
            neighborUnits.insert(neighborUnits.end(), 
                                neighborCells[i]->getInhabitingUnits().begin(), 
                                neighborCells[i]->getInhabitingUnits().end());
        }
    }
    return neighborUnits;
}
const std::vector<Cell*>& WorldGeometry::getNeighbors(i32 index){
    return mCells[index]->getNeighbors();
}
const std::vector<Cell*>& WorldGeometry::getCells(){
    return mCells;
}
const std::vector< std::vector<f32> >& WorldGeometry::getCellsDistance(){
    return cellsDistance;
}
const Vector2<f32> WorldGeometry::getSquadPosition(i32 _size, i32 _index) const{
    return squadPosition[_size][_index];
}
/* This is a fucking disaster, but works more or less */
//bool WorldGeometry::checkCollision(Vector2<f32> _orig, Vector2<f32> _end, f32 _halfsizeX, f32 _halfsizeY) const{
//    // Create the hitbox and the minimun distance to move
//    const f32 distanceMove = 40.0f;
//    Box2D hitBox(_halfsizeX, _halfsizeY);
//    hitBox.moveHitbox(_orig);
//
//    // Create vectorDir and the vectorOrigen which will save the actual position
//    Vector2<f32> vectorDir(_end - _orig);
//    Vector2<f32> vectorOrigen(_orig);
//
//    // Get the distance between both points and calculate the num of steps
//    f32 length = std::sqrt(std::pow(vectorDir.x, 2) + std::pow(vectorDir.y, 2));
//    f32 stepsBrute = length / distanceMove;
//    f32 steps = std::floor(stepsBrute);
//    stepsBrute -= steps;
//
//    // Calculate the vectorDir and multiples by the 'speed'
//    vectorDir = vectorDir / length;
//    vectorDir = vectorDir * distanceMove;
//
//    for(i32 i = 0; i < steps; i++){
//        vectorOrigen += vectorDir;
//        hitBox.moveHitbox(vectorOrigen);
//        std::cout << "Posicion hitbox: " << vectorOrigen.x << " , " << vectorOrigen.y << "\n";
//        if(quadTree->canBuild(hitBox)){
//            return true;
//        }
//    }
//    // Last steps
//    vectorOrigen += vectorDir * stepsBrute;
//    if(quadTree->canBuild(hitBox)){
//        return true;
//    }
//
//    return false;
//}

// Line collision test (faster, but less precise)
bool WorldGeometry::checkCollision(Vector2<f32> _orig, Vector2<f32> _end) const{
    // Test precision
    const f32 speed(10.0f);
    f32 totalDistance(0.0f);
    Vector2<f32> vectorOrig(_orig);
    Vector2<f32> vectorDirection(_end - _orig);
    
    if(vectorDirection.x != 0 || vectorDirection.y != 0){
        // Normalize vector 
        f32 vectorDistance(std::sqrt(std::pow(vectorDirection.x, 2) + 
                                     std::pow(vectorDirection.y, 2)));
        
        // Calculate speed vector
        vectorDirection = (vectorDirection / vectorDistance) * speed;
        
        // Iterate line collision
        while(totalDistance < vectorDistance){
            std::cout << "Check collision: " << totalDistance << "\n";
            vectorOrig += vectorDirection;
            totalDistance += speed;
            if(positionToCell(vectorOrig) != nullptr && positionToCell(vectorOrig)->isBlocked()){
                return true;
            }
        }
    }
   
    return false;
}