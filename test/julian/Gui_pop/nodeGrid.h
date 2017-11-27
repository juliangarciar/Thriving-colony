#ifndef NODEGRID_H
#define NODEGRID_H

#include <iostream>
#include <irrlicht.h>
class nodeGrid{
    private:
        int posX;
        int posY;
        bool visited;
        bool block;
        bool frontier;
        bool counted;
        int weight;
        int priority;
        
        nodeGrid* cameFrom;
        irr::scene::ISceneManager *smgr;
        irr::scene::IMeshSceneNode *cube;

      public:
        nodeGrid(int x, int y, irr::scene::ISceneManager *smgrData);
        nodeGrid(const nodeGrid& orig);
        virtual ~nodeGrid();

        void swapColor(irr::video::SColor colorData);
        int getX();
        int getY();
        bool itsBlock();
        void setBlock(bool blockData);
        bool itsVisited();
        void setVisited(bool visitedData);
        bool itsFrontier();
        void setFrontier(bool frontierData);
        int getWeight();
        void setWeight(int weightData);
        bool itsCounted();
        void setCounted(bool countedData);
        nodeGrid* getCameFrom();
        void setCameFrom(nodeGrid* cameFromData);
        irr::scene::IMeshSceneNode *getCube();
        int getPriority();
        void setPriority(int priorityData);
};
#endif /* NODEGRID_H */