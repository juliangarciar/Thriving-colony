#ifndef NODEGRID_H
#define NODEGRID_H

#include <iostream>
#include <irrlicht.h>
class nodeGrid{
    private:
        i32 posX;
        i32 posY;
        bool diag;
        bool block;
        bool frontier;
        bool counted;
        f32 weight;
        f32 priority;
        
        nodeGrid* cameFrom;
        irr::scene::ISceneManager *smgr;
        irr::scene::IMeshSceneNode *cube;

      public:
        nodeGrid(i32 x, i32 y, i32 z, irr::scene::ISceneManager *smgrData);
        nodeGrid(const nodeGrid& orig);
        virtual ~nodeGrid();

        void swapColor(irr::video::SColor colorData);
        i32 getX();
        i32 getY();
        bool itsBlock();
        void setBlock(bool blockData);
        bool itsDiag();
        void setDiag(bool diagData);
        bool itsFrontier();
        void setFrontier(bool frontierData);
        f32 getWeight();
        void setWeight(f32 weightData);
        bool itsCounted();
        void setCounted(bool countedData);
        nodeGrid* getCameFrom();
        void setCameFrom(nodeGrid* cameFromData);
        irr::scene::IMeshSceneNode *getCube();
        f32 getPriority();
        void setPriority(f32 priorityData);
};
#endif /* NODEGRID_H */