#include <iostream>
#include <queue>
#include "grid.h"
#include "nodeGrid.h"

class aStar{
private:
    struct comparePriority{
        bool operator()(nodeGrid* const & p1, nodeGrid* const & p2 ){
            return p1->getPriority() > p2->getPriority();
        };
    };
    bool finish;
    int newCost;
    int priority;
    nodeGrid* start;
    nodeGrid* end;
    nodeGrid* current;
    grid* map;
    std::vector< nodeGrid* > neighbors;
    std::priority_queue< nodeGrid*, std::vector < nodeGrid* >, comparePriority> frontier;
    
public:
    aStar(grid* mapData, nodeGrid* startData, nodeGrid* endData);
    aStar(const aStar &orig);
    virtual ~aStar();
    void startAlgoritm();
};