#include "PathManager.h"
#include "AStar.h"
#include "AStar2.h"
#include <Unit.h>
#include <WorldEngine/WorldGeometry.h>
#include <WorldEngine/Cell.h>

PathManager::PathManager(Unit* unitPtr){
    propietary = unitPtr;
}
PathManager::~PathManager(){
    
}
/* I need a second system to check the targetCell */
bool PathManager::createPathTo(Vector2<f32> targetPos){
/* Need of a search algorithm in order to get a viable Cell */
    AStar2* cellSearcher;
    Cell* origin = WorldGeometry::Instance()->positionToCell(propietary->getPosition()->toVector2());
    Cell* end = WorldGeometry::Instance()->positionToCell(targetPos);
    if(end->isBlocked()){
        std::cout << "Iniciando localizador de celula. \n";
        cellSearcher = new AStar2(end, origin);
        cellSearcher->Search();
        end = cellSearcher->getValidCell();
    }
    AStar* astar = new AStar(origin, end);

    astar->Search();
    propietary->setPath(astar->getPath());
    return true;
}