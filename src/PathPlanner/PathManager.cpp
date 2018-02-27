#include "PathManager.h"
#include "AStar.h"
#include <Unit.h>
#include <WorldEngine/WorldGeometry.h>
#include <WorldEngine/Cell.h>
#define spaceWidth 10240
#define total 80

PathManager::PathManager(Unit* unitPtr){
    // Creates the graph
    //mapGeometry = WorldGeometry::Instance();
    propietary = unitPtr;
}
PathManager::~PathManager(){
}
// Change this method
//i32 PathManager::getClosestNodeToPosition(Vector2<f32>& pos){
//    // This is not working properly for some reason
//    i32 idx = (i32)(total * pos.x / spaceWidth) + 
//                ((i32)((total) * pos.y / spaceWidth) * total);
//    if (idx > mapMaster->getGraph()->getNumNodes() - 1) 
//        idx = mapMaster->getGraph()->getNumNodes() - 1;
//    return idx;
//}
//i32 PathManager::getClosestValidNode(Vector2<f32>& pos){
//    i32 idx = getClosestNodeToPosition(pos);
//    //SearchDijkstra dijkstra(mapMaster->getGraph(), idx);
//    //idx = dijkstra.getTarget();
//    return idx;
//}
bool PathManager::createPathTo(Vector2<f32> targetPos){
    //vDestination = targetPos;
    Cell* origin = WorldGeometry::Instance()->positionToCell(propietary->getPosition()->toVector2());
    Cell* end = WorldGeometry::Instance()->positionToCell(targetPos);
    AStar* astar = new AStar(origin, end);

    // Dummy variable, to be deleted
    //bool obstructed = false;
    // If the location is not obstructed from the unit position
    // a path doesn't need to be calculated
    //if(!obstructed){
    //    path.push_back(targetPos);
    //    return true;
    //}
    // Find closes node to unitPos
    //i32 closestNodeToUnit = getClosestNodeToPosition(unit->getPosition()->toVector2());
    //if(closestNodeToUnit == no_closest_node_found)
    //    return false;

    // Same for target
    //i32 closestNodeToTarget = getClosestNodeToPosition(targetPos);
    //if(closestNodeToTarget == no_closest_node_found)
    //    return false;

    //SearchAStar aStar(*mapMaster->getGraph(), closestNodeToUnit, closestNodeToTarget);

    // Complete getPathToTarget
    //std::list<i32> dummy = aStar.getPathToTarget();
    std::list< Vector2<f32> > path;
    std::vector<Cell*> pathCell = astar->Search();
    std::cout <<"Me muerto "<< pathCell.size() << "\n";
    for(i32 i = 0; i < pathCell.size(); i++){
        path.push_back(pathCell[i]->getPosition());
    }
    //std::cout <<"Me muerto \n";
    //path.push_back(targetPos);
    //if(!dummy.empty()){
        //path.clear();
        //while(!dummy.empty()){
        //    path.push_back(mapMaster->getGraph()->getNodeVector().at(dummy.front()).getPosition());
        //    dummy.pop_front();
        //}
        // Complete this method
        // maybe is needed as nodes, instead of edges 
        //convertIndicesToVectors(pathOfNode, path);
        // Add the actual target position to the end of the path
        //.push_back(targetPos);
        propietary->setPath(path);
        //std::cout << "Tamanyo del camino a seguir " << path.size() << "\n";
        return true;
    //}
    // No path found
    //else
    //    return false;
}