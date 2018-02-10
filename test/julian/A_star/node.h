#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <SFML/Graphics.hpp>

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
        sf::RectangleShape *rectangle;
        
    public:
        node(i32 x, i32 y);
        node(const node& orig);
        virtual ~node();

        void swapColor(sf::Color color);
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
        sf::RectangleShape *getRectangle();
        i32 getPriority();
        void setPriority(i32 priorityData);
};
#endif /* NODE_H */