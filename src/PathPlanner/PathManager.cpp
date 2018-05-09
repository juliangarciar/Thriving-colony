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
    Cell* origin = WorldGeometry::Instance()->positionToCell(propietary->getPosition());
    Cell* end = WorldGeometry::Instance()->positionToCell(targetPos);
    if(end->isBlocked()){
        end = WorldGeometry::Instance()->getValidCell(end, origin, nullptr);
    }
    //AStar* astar = new AStar(origin, end);

    //astar->Search();
    std::list< Vector2<f32> > tmp;
    tmp.push_back(end->getPosition());
    //propietary->setPath(astar->getPath());
    propietary->setPath(tmp);
    return true;
}