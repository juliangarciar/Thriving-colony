#ifndef PATHMANAGER_H
#define PATHMANAGER_H

#include "SearchAStar.h"
#include <vector>
#include <queue>
class PathManager{
    private:
    // PathManager instance
        static PathManager* pinstance;
        enum {no_closest_node_found = -1};
    // A pointer to the owned of this class 
    // this won't be neccesary

    // A local reference to the navgraph
        Graph navGraph;
    // Position the unit wants to plan a path
        Vector2<float> vDestination;
    
    public:
    // Constructor
        static PathManager* Instance();
        PathManager();
        PathManager(const PathManager &orig);
        virtual ~PathManager();
    // Closest node to the unit maybe this is not needed
        int getClosestNodeToPosition(Vector2<float> pos);
    // Finds the least cost path between unit's position and the target
    // returns true and a list full of waypoints if successful.
    // Returns false if else.
        bool createPathTo(Vector2<float> unitPos, Vector2<float> targetPos, std::list< Vector2<float> >& path);

};
#endif /* PATHMANAGER_H */