#ifndef MAPMASTER_H
#define MAPMASTER_H
#include <PathPlanner/Graph.h>
#include "CellSpacePartition.h"
#include <list>
#include <Types.h>
class MapMaster{
    private:
        static MapMaster* pinstance;
        Graph* navGraph;
        CellSpacePartition* geometryMap;
        std::map< int, Cell* > validationMap;
        void Init();
    public: 
        static MapMaster* Instance();
        MapMaster();
        ~MapMaster();
    // Getters
        Graph* getGraph();
        CellSpacePartition* getGeometry();
        std::list< Edge > getValidatedEdges(i32 index);
        //bool checkCollisions(Vector2<f32> origin, Vector2<f32> targetPosition);
};
#endif /* MAPMASTER_H */