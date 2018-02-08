#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <irrlicht.h>
class node{
    private:
        i32 posX;
        i32 posY;
        bool visited;
        bool block;
        bool frontier;
        bool counted;
        i32 weight;
        i32 priority;
        
        node* cameFrom;
        //sf::RectangleShape *rectangle;
        irr::scene::ISceneManager *smgr;
        irr::scene::IMeshSceneNode *cube;

      public:
        node(i32 x, i32 y, irr::scene::ISceneManager *smgrData);
        node(const node& orig);
        virtual ~node();

        void swapColor(irr::video::SColor colorData);
        i32 getX();
        i32 getY();
        bool itsBlock();
        void setBlock(bool blockData);
        bool itsVisited();
        void setVisited(bool visitedData);
        bool itsFrontier();
        void setFrontier(bool frontierData);
        i32 getWeight();
        void setWeight(i32 weightData);
        bool itsCounted();
        void setCounted(bool countedData);
        node* getCameFrom();
        void setCameFrom(node* cameFromData);
        irr::scene::IMeshSceneNode *getCube();
        i32 getPriority();
        void setPriority(i32 priorityData);
};
#endif /* NODE_H */