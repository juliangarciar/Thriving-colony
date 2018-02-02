#include "PathManager.h"

PathManager* PathManager::pinstance = 0;

PathManager* PathManager::Instance() {
    if(pinstance == 0) {
        pinstance = new PathManager();
    }
    return pinstance;
}
PathManager::PathManager(){
    // Creates the graph
    this->navGraph = Graph();
    LWayPoint a = LWayPoint(Vector2<float>(8000, 8000));
    LWayPoint b = LWayPoint(Vector2<float>(2000, 8000));
    LWayPoint c = LWayPoint(Vector2<float>(8000, 2000));
    LWayPoint d = LWayPoint(Vector2<float>(2000, 2000));
    navGraph.addNode(a);
    navGraph.addNode(b);
    navGraph.addNode(c);
    navGraph.addNode(d);
    // Add the edges
}
PathManager::~PathManager(){

}
bool PathManager::createPathTo(Vector2<float> unitPos, Vector2<float> targetPos, std::list< Vector2<float> >& path){
    vDestination = targetPos;
    // Dummy variable, to be deleted
    bool obstructed = false;
    // If the location is not obstructed from the unit position
    // a path doesn't need to be calculated
    if(!obstructed){
        path.push_back(targetPos);
        return true;
    }
    // Find closes node to unitPos
    int closestNodeToUnit = getClosestNodeToPosition(unitPos);
    if(closestNodeToUnit == no_closest_node_found)
        return false;

    // Same for target
    int closestNodeToTarget = getClosestNodeToPosition(targetPos);
    if(closestNodeToTarget == no_closest_node_found)
        return false;

    SearchAStar aStar(navGraph, closestNodeToUnit, closestNodeToTarget);

    // Complete getPathToTarget
    std::list<int> dummy = aStar.getPathToTarget();

    if(!dummy.empty()){
        path.clear();
        for(int i = 0; i < dummy.size(); i++){
            path.push_back(navGraph.getNode(dummy.front()).getPosition());
            dummy.pop_front();
        }
        // Complete this method
        // maybe is needed as nodes, instead of edges 
        //convertIndicesToVectors(pathOfNode, path);
        // Add the actual target position to the end of the path
        path.push_back(targetPos);
        return true;
    }
    // No path found
    else
        return false;
}