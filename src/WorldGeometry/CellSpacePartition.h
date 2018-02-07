#ifndef CELLSPACEPARTITION_H
#define CELLSPACEPARTITION_H
#include "../Entity.h"
#include "../GraphicEngine/Vector2.h"
#include "../GraphicEngine/Box2D.h"
#include <irrlicht.h>
#include <vector>
#include <list>

class CellSpacePartition;
struct Cell{
// All the entities inhabiting this cell
    std::list< Entity* > entities;
// Cell bounding box
    Box2D BBox;
// Constructor
    Cell(Vector2<float> topLeft,
         Vector2<float> botRight):BBox(topLeft, botRight)
    {}
// Destructor
    ~Cell();
};
class CellSpacePartition{
    private:
    // Width and height
        float spaceWidth;
        float spaceHeight;
    // Number of cells the space is going to be divided into
        int cellsX;
        int cellsY;
    
        float cellSizeX;
        float cellSizeY;
    // Required number of cells
        std::vector< Cell > mCells;
    // Stores valid neighbors 
        std::vector< Entity* > mNeighbors;
    // Iterator used by methods next and begin
        std::vector< Entity* >::iterator mCurNeighbor;
    // Returns an index from a position 
        int positionToIndex(Vector2<float> position);
    public:
    // Constructor
        CellSpacePartition( float width,
                            float height,
                            int nCellsX,
                            int nCellsY,
                            int maxEntities);
    // Destructor
        ~CellSpacePartition();
    // Add entities to the proper cell
        inline void addEntity(Entity* ent);
    // Updates a entity's cell, calling this from the entity update method
        inline void updateEntity(Entity* ent, Vector2<float> oldPos);
    // Calculate neighbors and add them in the neighbor vector
        inline void calculateNeighbors(Vector2<float> targetPos, float radious);
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