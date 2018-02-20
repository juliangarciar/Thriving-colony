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
    geometryMap = new CellSpacePartition(MAPX, MAPY, SPACEX, SPACEY);
    navGraph = new Graph(MAPX, MAPY, SPACEX, SPACEY);
    //std::vector< Cell* > cells = geometryMap->get
    for(i32 i = 0; i < navGraph->getNumNodes(); i++){
        Cell* tmp = geometryMap->positionToCell(navGraph->getNode(i).getPosition());
        tmp->setBlocked(false);
        validationMap[i] = tmp;
    }
}
MapMaster::~MapMaster(){
    delete navGraph;
    delete geometryMap;
}
Graph* MapMaster::getGraph(){
    return navGraph;
}
CellSpacePartition* MapMaster::getGeometry(){
    return geometryMap;
}
std::list< Edge > MapMaster::getValidatedEdges(i32 index){
    std::list< Edge > tmp = navGraph->getEdgeListVector(index);
    std::list< Edge > dummy;
    // Cambiar estas cositas
    std::list< Edge >::iterator it;
    for(it = tmp.begin(); it != tmp.end(); it++){
        if(!geometryMap -> positionToCell(navGraph->getNode(it->getTo()).getPosition())->isBlocked()){
            dummy.push_back(*it);
        }
    }
    return dummy;
}
//bool MasterMap::checkCollisions(Vector2<f32> origin, Vector2<f32> targetPosition){
//    std::vector< Entity* > totalNeighbors;
//    Cell* idx = positionToCell(origin);
//    std::vector< Cell* > neighbors = idx->getNearNeighbors();
//    if(idx != NULL && idx->isBlocked()){
//        return false;
//    }
//    else{
//        for(i32 i = 0; i < neighbors.size(); i++){
//            if(neighbors.at(i)->getInhabitingBuilding() != 0){
//                //totalNeighbors.push_back(neighbors.at(i).getInhabitingBuilding);
//                std::cout << "Existen entidades cercanas.\n";
//            }
//        }
//        return true;
//    }
//}