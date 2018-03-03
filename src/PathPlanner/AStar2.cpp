#include "AStar2.h"
#include <WorldEngine/WorldGeometry.h>
#include <WorldEngine/Cell.h>
#include "PriorityQueue.h"
#define MAX 16384
AStar2::AStar2(Cell* source, Cell* target){
    worldGeometry = WorldGeometry::Instance();
    
    sourceCell = source;
    targetCell = target;
    sourceIndex = source->getIndex();
    targetIndex = target->getIndex();
    
    GCosts = std::vector<f32>(MAX, 0);
    FCosts = std::vector<f32>(MAX, 0);

    shortestPath = std::vector<Cell*>(MAX, NULL);
    searchFrontier = std::vector<Cell*>(MAX, NULL);

    validCell = NULL;
}
AStar2::~AStar2(){
    shortestPath.clear();
    searchFrontier.clear();
    GCosts.clear();
    FCosts.clear();
}

void AStar2::Search(){
    IndexedPriorityQLow<float> pq(FCosts, MAX);
    pq.insert(sourceIndex);
    while(!pq.empty()){
        i32 closestIndex = pq.Pop();
        std::cout << "Selected index: " << closestIndex << "\n";
    /* Adds the cell to the path vector */
        shortestPath[closestIndex] = searchFrontier[closestIndex];

    /* Stop condition, research about a system of conditions */
        if(!worldGeometry->indexToCell(closestIndex)->isBlocked()) {
            validCell = worldGeometry->indexToCell(closestIndex);
            return ;
        }
    /* Get neighbors of the chosen cell */
        std::vector<Cell*> neighbors = worldGeometry->getNeighbors(closestIndex);
        std::cout << "Checking neighbors \n";
    /* Calculate the cost for each neighbor to the targetCell */
        for(i32 i = 0; i < neighbors.size(); i++){
            i32 potentialNode = neighbors[i]->getIndex();
            f32 HCost = worldGeometry->calculateDistance(neighbors[i]->getPosition(), targetCell->getPosition());
            f32 GCost = GCosts[closestIndex] + worldGeometry->getCost(closestIndex, i);
            std::cout << "Distancia H: " << HCost << "\n";
            std::cout << "Distancia G: " << GCost << "\n";
            if(searchFrontier[potentialNode] == NULL){
                FCosts[potentialNode] = GCost + HCost;
                GCosts[potentialNode] = GCost;

                pq.insert(potentialNode);
                searchFrontier[potentialNode] = worldGeometry->indexToCell(closestIndex);
            }
        /* Fix this method, isn't working properly */
            else if((GCost < GCosts[potentialNode]) && (shortestPath[potentialNode] == NULL)){
                FCosts[potentialNode] = GCost + HCost;
                GCosts[potentialNode] = GCost;

                searchFrontier[potentialNode] = worldGeometry->indexToCell(closestIndex);
            }    
        }
    }
}
Cell* AStar2::getValidCell(){
    return validCell; 
}