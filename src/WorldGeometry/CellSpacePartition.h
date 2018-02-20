#ifndef CELLSPACEPARTITION_H
#define CELLSPACEPARTITION_H
#include <vector>
#include <list>
#include <Entity.h>
#include <Types.h>
#include <MathEngine/Vector2.h>
#include <MathEngine/Box2D.h>

class CellSpacePartition;
class Cell{
    private:
        Entity* inhabitingBuilding;
        std::vector< Entity* > inhabitingUnits;
        std::vector< Cell* > nearNeighbors;
    // Cell bounding box
        Box2D BBox;
    // Cell index
        i32 index;
    // Bool block
        bool blocked;
        bool mainRoad;
    public:
    // Constructor
        Cell(Vector2<f32> topLeft, Vector2<f32> botRight);
    // Destructor
        ~Cell();
    // Setters
        void setBlocked(bool data);
        void setMainRoad(bool data);
        void setInhabitingBuilding(Entity* building);
        void setInhabitingUnit(Entity* unit);
        void setNearNeighbor(Cell* neighbor);
        void setIndex(i32 index);
        void clearBuilding();
        void clearUnit(Entity* unit);
        void Clear();
    // Getters
        bool isBlocked();
        bool isMainRoad();
        bool canBuild();
        Box2D getHitBox();
        Entity* getInhabitingBuilding();
        std::vector< Entity* > getInhabitingUnits();
        std::vector< Cell* > getNearNeighbors();
        i32 getIndex();
};
class CellSpacePartition{
    private:
    // Required number of cells
        std::vector< Cell* > mCells;
    // Stores valid neighbors 
        std::vector< Entity* > mNeighbors;
    // Self explanatory variables
        i32 mapX, mapY, cellX, cellY, nCellsX, nCellsY;
    public:
        CellSpacePartition(i32 width, i32 height, i32 spaceX, i32 spaceY);
    // Destructor
        ~CellSpacePartition();
    // Updates a entity's cell, calling this from the entity update method
        void updateUnitCell(Entity* unit, Vector2<f32> oldPos);
    // Updates a cell
        void updateBuildingCell(Entity *object);
    // Clears the cells
        void clearCells();
    // Returns the correct position where the building is built
        Vector3<f32> correctBuildingPosition(Vector3<f32> targetPos, Entity *object, bool &collision);
    // Check collisions between an agent and a position
        //bool checkCollisions(Vector2<f32> origin, Vector2<f32> targetPosition);
    // Checks if the cell is blocked
        bool isBlocked(Vector2<f32> targetPos);
        bool sameCell(Vector2<f32> oldPos, Vector2<f32> newPos);
    // Returns an index from a position 
        Cell* positionToCell(Vector2<f32> position);
};
#endif /* CELLSPACEPARTITION_H */