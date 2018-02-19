#ifndef MAPMASTER_H
#define MAPMASTER_H
#include "Graph.h"
#include <WorldGeometry/CellSpacePartition.h>
class MapMaster{
    private:
        static MapMaster* pinstance;
        Graph* navGraph;
        CellSpacePartition* geometryMap;
        void Init();
    public: 
        static MapMaster* Instance();
        MapMaster();
        ~MapMaster();
    // Getters
        Graph* getGraph();
        CellSpacePartition* getGeometry();
};
#endif /* MAPMASTER_H */