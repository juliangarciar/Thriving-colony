#include "WorldGeometry.h"
#include "Cell.h"
#include "Quadtree.h"
#include <MathEngine/Vector2.h>
#define MAP 10240
#define CELL 80
WorldGeometry* WorldGeometry::pinstance = 0;
WorldGeometry* WorldGeometry::Instance(){
    if(pinstance == 0){
        pinstance = new WorldGeometry();
        pinstance->Init();
    }
    return pinstance;
}
WorldGeometry::WorldGeometry(){

}
WorldGeometry::~WorldGeometry(){
    mCells.clear();
    delete quadTree;
}
void WorldGeometry::Init(){
    i32 maxCells = MAP / CELL;
    //I32 total = maxCells * maxCells;
    for (i32 y = 0; y < maxCells; y++)
    {
        for (i32 x = 0; x < maxCells; x++)
        {
            f32 dX  = x * CELL + CELL/2;
            f32 dY = y * CELL + CELL/2;
            Vector2<f32> tmp = Vector2<f32>(dX, dY);
            Cell* cell = new Cell(tmp, (y * maxCells + x), CELL / 2);
            mCells.push_back(cell);
        }
    }
    std::cout << "WorldGeometry = " << mCells.size() << "\n";
}