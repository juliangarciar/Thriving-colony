#include "AStar.h"
#include <iostream>

aStar::aStar(grid *mapData, nodeGrid *startData, nodeGrid *endData)
{
    finish = false;
    start = startData;
    end = endData;
    newCost = 0;
    priority = 0;
    map = mapData;
}

aStar::~aStar()
{
    delete start;
    delete end;
    delete current;
    delete map;
    for (std::vector<nodeGrid *>::iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        delete (*it);
    }
    neighbors.clear();
    for (int i = 0; i < frontier.size(); i++)
    {
        frontier.pop();
    }
}

std::vector<nodeGrid *> aStar::startAlgoritm()
{

    std::vector<nodeGrid *> path;
    //Start algorithm
    frontier.push(start);
    while (!finish)
    {
        current = frontier.top();
        frontier.pop();

        neighbors = map->getNeighbours(current);
        for (int i = 0; i < neighbors.size(); i++)
        {
            if (neighbors[i]->itsDiag())
            {
                newCost = current->getWeight() + sqrt(2.00);
            }
            else
            {
                newCost = current->getWeight() + 1;
            }
            if ((neighbors[i]->itsCounted() == false) || (newCost < neighbors[i]->getWeight()))
            {
                //Realle needed ?
                //int dx1 = neighbors[i]->getX() - end->getX();
                //int dy1 = neighbors[i]->getY() - end->getY();
                //int dx2 = start->getX() - end->getX();
                //int dy2 = start->getY() - end->getY();
                //int cross = abs(dx1 * dy2 - dx2 * dy1);

                neighbors[i]->swapColor(irr::video::SColor(0, 127, 0, 127));
                neighbors[i]->setWeight(newCost);
                neighbors[i]->setCounted(true);
                priority = map->checkDistance(end, neighbors[i], start) + newCost;
                //priority += newCost;
                neighbors[i]->setPriority(priority);
                neighbors[i]->setCameFrom(current);
                frontier.push(neighbors[i]);
            }
        }
        if (current == end)
        {
            finish = true;
        }
        neighbors.clear();
    }
    //Show path

    while (current != start)
    {
        path.push_back(current);
        current = current->getCameFrom();
        current->swapColor(irr::video::SColor(0, 255, 0, 0));
    }
    end->swapColor(irr::video::SColor(0, 0, 255, 0));
    start->swapColor(irr::video::SColor(0, 0, 0, 255));

    path.swap(path);
    return path;
}