#ifndef WORLDGEOMETRY_H
#define WORLDGEOMETRY_H
#include <vector>
#include <Types.h>
class Cell;
class Quadtree;
class WorldGeometry{
    private:
        static WorldGeometry* pinstance;
        std::vector<Cell*> mCells;
        Quadtree* quadTree;
        //std::vector<f32> cellsDistance;
    public:
        static WorldGeometry* Instance();
        WorldGeometry();
        ~WorldGeometry();
        void Init();
};
#endif