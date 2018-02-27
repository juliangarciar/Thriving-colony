#ifndef ASTAR_H
#define ASTAR_H
#include <vector>
#include <Types.h>
#include <MathEngine/Vector2.h>

class WorldGeometry;
class Cell;
class AStar{
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
    public:
        /**
         * @brief Default constructor
         * 
         * @param source The source cell where the unit is allocated in
         * @param target The target cell where the unit pretend to go
         */
        AStar(Cell* source, Cell* target);
        /**
         * @brief Default destructor
         * 
         */
        ~AStar();
        /**
         * @brief Search for a path to the constructor's targetCell
         * 
         * @return std::vector<Cell*> Returns a vector of cells that indicates the path to follow
         */
        void Search();
        std::vector<Cell*> getPath();
};
#endif /* ASTAR_H */