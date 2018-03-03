#ifndef ASTAR2_H
#define ASTAR2_H

#include <vector>
#include <list>
#include <Types.h>
#include <MathEngine/Vector2.h>

class WorldGeometry;
class Cell;
class AStar2{
    private:
        WorldGeometry* worldGeometry;

        std::vector< Cell* > shortestPath;
        std::vector< Cell* > searchFrontier;

        std::vector<f32> GCosts;
        std::vector<f32> FCosts;

        Cell* sourceCell;
        Cell* targetCell;

        i32 sourceIndex;
        i32 targetIndex;

        Cell* validCell;
    public:

        AStar2(Cell* source, Cell* target);
        ~AStar2();
        void Search();
        Cell* getValidCell();
};
#endif /* ASTAR2_H */