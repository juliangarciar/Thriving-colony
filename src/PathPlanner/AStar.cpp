#include "AStar.h"
#include <WorldEngine/WorldGeometry.h>
#include <WorldEngine/Cell.h>
#include "PriorityQueue.h"
#define MAX 16384
AStar::AStar(Cell* source, Cell* target){
    worldGeometry = WorldGeometry::Instance();
    
    sourceCell = source;
    targetCell = target;
    sourceIndex = source->getIndex();
    targetIndex = target->getIndex();
    
    GCosts = std::vector<f32>(MAX, 0.0);
    FCosts = std::vector<f32>(MAX, 0.0);

    shortestPath = std::vector<Cell*>(MAX);
    searchFrontier = std::vector<Cell*>(MAX);
}
AStar::~AStar(){
    shortestPath.clear();
    searchFrontier.clear();
    GCosts.clear();
    FCosts.clear();
}
/* I'm sure this isn't working properly */
/* Delete searchedCells and the system to recover the path */
void AStar::Search(){
    IndexedPriorityQLow<float> pq(FCosts, MAX);
    pq.insert(sourceIndex);
    while(!pq.empty()){
        i32 closestIndex = pq.Pop();
    /* Adds the cell to the path vector */
        shortestPath[NextClosestNode] = searchFrontier[NextClosestNode];

    /* Stop condition, research about a system of conditions */
        if(closestIndex == targetIndex) {
            /* Do more things, like making the path of vectors */
            return shortestPath;
        }
    /* Get neighbors of the chosen cell */
        std::vector<Cell*> neighbors = worldGeometry->getNeighbors(closestIndex);
    /* Calculate the cost for each neighbor to the targetCell */
        for(i32 i = 0; i < neighbors.size(); i++){
            if(neighbors[i]->getInhabitingBuilding() == NULL && !neighbors[i]->isBlocked()){
                i32 potentialNode = neighbors[i]->getIndex();
                f32 HCost = worldGeometry->calculateDistance(neighbors[i]->getPosition(), targetCell->getPosition());
                f32 GCost = GCosts[closestIndex] + worldGeometry->getCost(closestIndex, potentialNode);

                if(searchFrontier[potentialNode] == NULL){
                    FCosts[potentialNode] = GCost + HCost;
                    GCosts[potentialNode] = GCost;

                    pq.insert(potentialNode);
                    searchFrontier[potentialNode] = neighbors[i];
                }
            /* Fix this method, isn't working properly */
                else if((GCost < GCosts[potentialNode]) && (searchedCells[potentialNode] == 0)){
                //else if((GCost < GCosts[potentialNode])){
                    FCosts[potentialNode] = GCost + HCost;
                    GCosts[potentialNode] = GCost;

                    searchFrontier[potentialNode] = neighbors[i];
                }    
            }
        }
    }
}
std::vector< Vector2<f32> > AStar::getPath(){
    std::vector< Vector2<f32> > dummyPath;
    //just return an empty path if no target or no path found
    if (targetIndex < 0)  return path;    

    i32 nd = targetIndex;
    pathDummy.push_front(nd);

    while ((nd != sourceIndex) && ( searchFrontier[nd] != 0))
    {
        nd =  shortestPath[nd]->getIndex();

        path.push_front(nd);
    }
    path.push_front(sourceIndex);
    return dummyPath;
}