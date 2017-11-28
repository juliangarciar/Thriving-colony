#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <queue>
#include "NodeGrid.h"

class grid
{
  private:
    nodeGrid ***map;
    int ox;
    int oy;
    irr::scene::ISceneManager *smgrData;

  public:
    grid(int x, int y, irr::scene::ISceneManager *smgrData);
    grid(const grid &orig);
    virtual ~grid();

    int getX() { return ox; };
    int getY() { return oy; };
    nodeGrid *getNode(int x, int y);
    float checkDistance(nodeGrid *a, nodeGrid *b, nodeGrid *startData);
    nodeGrid ***getGrid()
    {
        return map;
    };
    std::vector<nodeGrid *> getNeighbours(nodeGrid *currentData);
};
#endif /* GRID_H */