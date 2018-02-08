#ifndef CELLSPACEPARTITION_H
#define CELLSPACEPARTITION_H
#include "../Entity.h"
#include "../GraphicEngine/Vector2.h"
#include "../GraphicEngine/Box2D.h"
#include <irrlicht.h>
#include <vector>
#include <list>
#include <Types.h>

class CellSpacePartition;
struct Cell{
// All the entities inhabiting this cell
    std::list< Entity* > entities;
// Cell bounding box
    Box2D BBox;
// Constructor
    Cell(Vector2<f32> topLeft,
         Vector2<f32> botRight):BBox(topLeft, botRight)
    {}
// Destructor
    ~Cell();
};
class CellSpacePartition{
    private:
    // Width and height
        f32 spaceWidth;
        f32 spaceHeight;
    // Number of cells the space is going to be divided into
        i32 cellsX;
        i32 cellsY;
    
        f32 cellSizeX;
        f32 cellSizeY;
    // Required number of cells
        std::vector< Cell > mCells;
    // Stores valid neighbors 
        std::vector< Entity* > mNeighbors;
    // Iterator used by methods next and begin
        std::vector< Entity* >::iterator mCurNeighbor;
    // Returns an index from a position 
        i32 positionToIndex(Vector2<f32> position);
    public:
    // Constructor
        CellSpacePartition( f32 width,
                            f32 height,
                            i32 nCellsX,
                            i32 nCellsY,
                            i32 maxEntities);
    // Destructor
        ~CellSpacePartition();
    // Add entities to the proper cell
        inline void addEntity(Entity* ent);
    // Updates a entity's cell, calling this from the entity update method
        inline void updateEntity(Entity* ent, Vector2<f32> oldPos);
    // Calculate neighbors and add them in the neighbor vector
        inline void calculateNeighbors(Vector2<f32> targetPos, f32 radious);
    // Returns a reference to the entity of the neighbor vector
        Entity* begin();
    // Used to iterate trought the neighbor vector
        Entity* next();
    // Returns true if the iterator reach the end of the vector
        bool end();
    // Clears the cells
        void clearCells();
};
#endif /* CELLSPACEPARTITION_H */