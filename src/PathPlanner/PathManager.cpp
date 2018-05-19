#include "PathManager.h"
#include "AStar.h"
#include <Unit.h>
#include <WorldEngine/WorldGeometry.h>
#include <WorldEngine/Cell.h>

PathManager::PathManager(Unit* unitPtr):propietary(unitPtr){}

PathManager::~PathManager(){

}

bool PathManager::createPathTo(Vector2<f32> targetPos){
    Vector2<f32> initPos(propietary->getPosition());
    Vector2<f32> finalPos(0, 0);

    Cell* origin = WorldGeometry::Instance()->positionToCell(initPos);
    Cell* end = WorldGeometry::Instance()->getValidCell(targetPos, initPos, propietary->getHitbox());

    AStar astar(origin, end);
    astar.Search();
    std::list< Vector2<f32> > finalPath = astar.getPath();

    finalPath.push_front(initPos);
    /* Check for final path */
    Box2D tmp = propietary->getHitbox();
    tmp.moveHitbox(targetPos);

    if(WorldGeometry::Instance()->checkHitBoxCollision(tmp, false)){
        finalPath.push_back(targetPos);
    }

    /* Smooth the path */
    //std::cout << "Path sin smooth: " << finalPath.size();
    if(finalPath.size() > 2){
        /* Maybe make a hitbox test collision instead */
        smoothPath(finalPath);
    }    
    //std::cout << ". Con smooth: " << finalPath.size() << ".\n";
    propietary->setPath(finalPath);

    return true;
}

void PathManager::smoothPath(std::list< Vector2<f32> >& _path){
    std::list< Vector2<f32> >::iterator v1(_path.begin()), 
                                        v2(_path.begin()),
                                        v3(_path.begin());
    v2++;
    v3++;
    v3++;
    while(v2 != _path.end() && _path.size() > 2){
        if(!WorldGeometry::Instance()->checkLineCollision(*v1, *v3)){
            v2 = _path.erase(v2);
            v3++;
        }
        else{
            v1 = v2;
            v2++;
            v3++;
        }
    }
}