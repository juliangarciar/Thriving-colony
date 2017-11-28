#ifndef NODEGRID_H
#define NODEGRID_H

#include <iostream>
#include <irrlicht.h>
class nodeGrid
{
  private:
    int posX;
    int posY;
    bool diag;
    bool block;
    bool frontier;
    bool counted;
    float weight;
    float priority;

    nodeGrid *cameFrom;
    irr::scene::ISceneManager *smgr;
    irr::scene::IMeshSceneNode *cube;

  public:
    nodeGrid(int x, int y, int z, irr::scene::ISceneManager *smgrData);
    nodeGrid(const nodeGrid &orig);
    virtual ~nodeGrid();

    void swapColor(irr::video::SColor colorData);
    int getX();
    int getY();
    bool itsBlock();
    void setBlock(bool blockData);
    bool itsDiag();
    void setDiag(bool diagData);
    bool itsFrontier();
    void setFrontier(bool frontierData);
    float getWeight();
    void setWeight(float weightData);
    bool itsCounted();
    void setCounted(bool countedData);
    nodeGrid *getCameFrom();
    void setCameFrom(nodeGrid *cameFromData);
    irr::scene::IMeshSceneNode *getCube();
    float getPriority();
    void setPriority(float priorityData);
};
#endif /* NODEGRID_H */