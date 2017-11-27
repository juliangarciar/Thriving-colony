#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <queue>
#include "nodeGrid.h"

class grid
{
    private:
        nodeGrid*** map;
        int ox;
        int oy;
        irr::scene::ISceneManager *smgrData;
    public:
      grid(int x, int y, irr::scene::ISceneManager *smgrData);
      grid(const grid &orig);
      virtual ~grid();

      void getX();
      void getY();
      nodeGrid* getNode(int x, int y);
      int checkDistance(nodeGrid* a, nodeGrid* b);
      nodeGrid*** getGrid(){
          return map;
      };
      std::vector< nodeGrid* > getNeighbours(nodeGrid* currentData);
};
#endif /* GRID_H */