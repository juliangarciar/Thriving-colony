#include "MapMaster.h"
#define SPACEX 128
#define SPACEY 128
#define MAPX 10240
#define MAPY 10240
MapMaster* MapMaster::pinstance = 0;
MapMaster* MapMaster::Instance(){
    if(pinstance == 0){
        pinstance = new MapMaster();
    }
    return pinstance;
}
MapMaster::MapMaster(){
    navGraph = new Graph(MAPX, MAPY, SPACEX, SPACEY);
    geometryMap = new CellSpacePartition(MAPX, MAPY, SPACEX, SPACEY);
    // Extra functions
}
MapMaster::~MapMaster(){

}
Graph* MapMaster::getGraph(){
    return navGraph;
}
CellSpacePartition* MapMaster::getGeometry(){
    return geometryMap;
}