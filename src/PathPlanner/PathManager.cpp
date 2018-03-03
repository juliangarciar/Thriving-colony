#include "PathManager.h"
#include "AStar.h"
#include <Unit.h>
#include <WorldEngine/WorldGeometry.h>
#include <WorldEngine/Cell.h>

PathManager::PathManager(Unit* unitPtr){
    propietary = unitPtr;
}
PathManager::~PathManager(){
    
}
bool PathManager::createPathTo(Vector2<f32> targetPos){
    /* Need of a search algorithm in order to get a viable Cell */
    Cell* origin = WorldGeometry::Instance()->positionToCell(propietary->getPosition()->toVector2());
    Cell* end = WorldGeometry::Instance()->positionToCell(targetPos);
    AStar* astar = new AStar(origin, end);

    astar->Search();
    propietary->setPath(astar->getPath());
    return true;
}