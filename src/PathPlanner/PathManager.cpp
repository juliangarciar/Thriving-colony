#include "PathManager.h"
#include "SearchAStar.h"
#define spaceWidth 10240
#define total 80
PathManager::PathManager(class Unit* actor){
    // Creates the graph
    navGraph = Graph::Instance();
    unit = actor;
}
PathManager::~PathManager(){
    delete navGraph;
    delete unit;
}
// Change this method
int PathManager::getClosestNodeToPosition(Vector2<float> pos){
    // This is not working properly for some reason
    int idx = (int)(total * pos.x / spaceWidth) + 
                ((int)((total) * pos.y / spaceWidth) * total);
    std::cout << idx << "\n";
    std::cout << navGraph->getNumNodes() << std::endl;
    if (idx > navGraph->getNumNodes() - 1) 
        idx = navGraph->getNumNodes() - 1;

    return idx;
}
bool PathManager::createPathTo(Vector2<float> targetPos){
    vDestination = targetPos;
    // Dummy variable, to be deleted
    //bool obstructed = false;
    // If the location is not obstructed from the unit position
    // a path doesn't need to be calculated
    //if(!obstructed){
    //    path.push_back(targetPos);
    //    return true;
    //}
    // Find closes node to unitPos
    int closestNodeToUnit = getClosestNodeToPosition(unit->getPosition()->toVector2());
    if(closestNodeToUnit == no_closest_node_found)
        return false;

    // Same for target
    int closestNodeToTarget = getClosestNodeToPosition(targetPos);
    if(closestNodeToTarget == no_closest_node_found)
        return false;

    SearchAStar aStar(*navGraph, closestNodeToUnit, closestNodeToTarget);

    // Complete getPathToTarget
    std::list<int> dummy = aStar.getPathToTarget();
    std::list< Vector2<float> > path;
    if(!dummy.empty()){
        //path.clear();
        while(!dummy.empty()){
            path.push_back(navGraph->getPositionFrom(dummy.front()));
            dummy.pop_front();
        }
        // Complete this method
        // maybe is needed as nodes, instead of edges 
        //convertIndicesToVectors(pathOfNode, path);
        // Add the actual target position to the end of the path
        //path.push_back(targetPos);
        unit->setPath(path);
        std::cout << path.size() << "\n";
        return true;
    }
    // No path found
    else
        return false;
}