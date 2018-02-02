#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <queue>
#include "Grid.h"
#include "NodeGrid.h"

/**
 * @class aStar
 * @brief Crea un objeto tipo aStar
 */
class aStar
{
  private:
    struct comparePriority
    {
        bool operator()(nodeGrid *const &p1, nodeGrid *const &p2)
        {
            return p1 -> getPriority() > p2 -> getPriority();
        }
    };
    bool finish;
    float newCost;
    float priority;
    nodeGrid *start;
    nodeGrid *end;
    nodeGrid *current;
    grid *map;
    std::vector<nodeGrid *> neighbors;
    std::priority_queue<nodeGrid *, std::vector<nodeGrid *>, comparePriority> frontier;

public:
    /**
    * @brief Constructor de aStar
    * @param grid del mapa
    * @param nodo inicial
    * @param nodo final
    */
    aStar(grid *mapData, nodeGrid *startData, nodeGrid *endData);
    /**
	* @brief Destructor
	*/
    virtual ~aStar();
    
    std::vector<nodeGrid *> startAlgoritm();
};
#endif /* ASTAR_H */