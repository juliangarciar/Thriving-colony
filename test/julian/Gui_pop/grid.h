#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <queue>
#include "nodeGrid.h"

class grid
{
    private:
        nodeGrid*** map;
        i32 ox;
        i32 oy;
        irr::scene::ISceneManager *smgrData;
    public:
      grid(i32 x, i32 y, irr::scene::ISceneManager *smgrData);
      grid(const grid &orig);
      virtual ~grid();

      i32 getX(){return ox;};
      i32 getY(){return oy;};
      nodeGrid* getNode(i32 x, i32 y);
      f32 checkDistance(nodeGrid* a, nodeGrid* b, nodeGrid* startData);
      nodeGrid*** getGrid(){
          return map;
      };
      std::vector< nodeGrid* > getNeighbours(nodeGrid* currentData);
};
#endif /* GRID_H */