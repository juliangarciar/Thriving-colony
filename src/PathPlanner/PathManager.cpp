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
    // swap this to graph
    this->navGraph = Graph();
    LWayPoint a = LWayPoint(Vector2<float>(8000, 8000));
    LWayPoint b = LWayPoint(Vector2<float>(2000, 8000));
    LWayPoint c = LWayPoint(Vector2<float>(8000, 2000));
    LWayPoint d = LWayPoint(Vector2<float>(2000, 2000));
    navGraph.addNode(a);
    navGraph.addNode(b);
    navGraph.addNode(c);
    navGraph.addNode(d);
    Edge ab = Edge();
    Edge bc = Edge();
    Edge cd = Edge();
    Edge da = Edge();
    ab.setFrom(a.getIndex()), ab.setTo(b.getIndex());
    bc.setFrom(b.getIndex()), bc.setTo(c.getIndex());
    cd.setFrom(c.getIndex()), cd.setTo(d.getIndex());
    da.setFrom(d.getIndex()), da.setTo(a.getIndex());
}
PathManager::~PathManager(){

}
int PathManager::getClosestNodeToPosition(Vector2<float> pos){
    float distance = 10000000;
    Vector2<float> b;
    int chosen = -1;
    for(int i = 0; i < navGraph.getNumNodes(); i++){
        b = navGraph.getNode(i).getPosition();
        float dX = pos.x - b.x;
        float dY = pos.y - b.y;
        float dummy = std::sqrt(std::pow(dX, 2) + std::pow(dY, 2));
        if(dummy < distance){
            distance = dummy;
            chosen = i;
        }
    }
    return chosen;
}
bool PathManager::createPathTo(Vector2<float> unitPos, Vector2<float> targetPos, std::list< Vector2<float> >& path){
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
        while(!dummy.empty()){
            path.push_back(navGraph.getPositionFrom(dummy.front()));
            dummy.pop_front();
        }
        // Complete this method
        // maybe is needed as nodes, instead of edges 
        //convertIndicesToVectors(pathOfNode, path);
        // Add the actual target position to the end of the path
        path.push_back(targetPos);
        std::cout << path.size() << "\n";
        return true;
    }
    // No path found
    else
        return false;
}