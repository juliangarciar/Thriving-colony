#include "aStar.h"
aStar::aStar(grid* mapData, nodeGrid* startData, nodeGrid* endData){
    finish = false;
    start = startData;
    end = endData;
    newCost = 0;
    priority = 0;
    map = mapData;
}
aStar::aStar(const aStar &orig){

}
aStar::~aStar(){
    delete start;
    delete end;
    delete current;
    delete map;
    for (std::vector< nodeGrid* >::iterator it = neighbors.begin() ; it != neighbors.end(); ++it)
    {
        delete (*it);
    } 
    neighbors.clear();
    for (int i = 0; i < frontier.size(); i++){
        frontier.pop();
    }
}
void aStar::startAlgoritm(){
    //Start algorithm
    frontier.push(start);
    while (!finish)
    {
        current = frontier.top();
        frontier.top()->setVisited(true);
        frontier.pop();
        //Show path
        if (current == end)
        {
            finish = true;
            end->swapColor(irr::video::SColor(0, 255, 0, 0));

            while (current != start)
            {
                current = current->getCameFrom();
                current->swapColor(irr::video::SColor(0, 255, 0, 0));
            }
        }

        neighbors = map->getNeighbours(current);
        for (int i = 0; i < neighbors.size(); i++)
        {
            newCost = current->getWeight() + 1;
            if (!frontier.top()->itsCounted() || newCost < neighbors[i]->getWeight())
            {
                neighbors[i]->swapColor(irr::video::SColor(0, 127, 0, 127));
                neighbors[i]->setWeight(newCost);
                neighbors[i]->setCounted(true);
                priority = newCost + map->checkDistance(end, neighbors[i]);
                neighbors[i]->setPriority(priority);
                frontier.push(neighbors[i]);
                neighbors[i]->setCameFrom(current);
            }
        }
        neighbors.clear();
    }
}