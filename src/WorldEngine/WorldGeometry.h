#ifndef WORLDGEOMETRY_H
#define WORLDGEOMETRY_H

#include <vector>
#include <Types.h>

template <class T>
class Vector2;
class Cell;
class Quadtree;
class Building;
class WorldGeometry{
    private:
        static WorldGeometry* pinstance;
        std::vector<Cell*> mCells;
        Quadtree* quadTree;
        std::vector< std::vector<f32> > cellsDistance;
    public:
        /**
         * @brief Singleton pattern
         * 
         * @return WorldGeometry* 
         */
        static WorldGeometry* Instance();
        /**
         * @brief Default constructor (anyway, is the Init() method which really construct the object)
         * 
         */
        WorldGeometry();
        /**
         * @brief Default destructor
         * 
         */
        ~WorldGeometry();
        /**
         * @brief Inits the container data (called only from the instance generator)
         * 
         */
        void Init();
        /**
         * @brief Clears the container in order to create a new game
         * 
         */
        void Clear();
        /**
         * @brief Given a buildingPtr, assign it to the cells that collides with
         * 
         * @param buildingPtr 
         */
        void build(Building* buildingPtr);
        /**
         * @brief Returns a correct position to construct in
         * 
         * @param targetPos The position where the mouse is clicked
         * @param buildingPtr A pointer to the building that is intended to be built
         * @param collision Assigns true or false, depending if it collides with already built buildings
         * @return Vector2<f32> The correct position
         */
        Vector2<f32> correctBuildingPosition(Vector2<f32> targetPos, Building* buildingPtr, bool &collision);
        /**
         * @brief Transforms a position (Vector2) into the cell that collides with
         * 
         * @param position The position to be transformed
         * @return Cell* The cell colliding with the position
         */
        Cell* positionToCell(Vector2<f32> position);
        /**
         * @brief Returns a cell from an index
         * 
         * @param index The index in the cell's vector
         * @return Cell* The indexed cell
         */
        Cell* indexToCell(i32 index);
        /**
         * @brief Calculates the distance between two given points, it doesn't matter the order
         * 
         * @param a Point 1
         * @param b Point 2
         * @return f32 The distance in float format
         */
        f32 calculateDistance(Vector2<f32> a, Vector2<f32> b);
        /**
         * @brief Given two cell's index, calculates the cost to travel from one to another
         * 
         * @param indexA The cell index where the unit is at
         * @param indexB The cell index where the unit pretend to go
         * @return f32 The distance between them in float format
         */
        f32 getCost(i32 indexA, i32 indexB);
        /**
         * @brief A reference to the neighbors of a given cell index
         * 
         * @param index The index of the cell
         * @return const std::vector<Cell*>& The reference
         */
        const std::vector<Cell*>& getNeighbors(i32 index);
        /**
         * @brief Returns a reference to the cell's vector
         * 
         * @return const std::vector<Cell*>& Self-explanatory
         */
        const std::vector<Cell*>& getCells();
        /**
         * @brief A reference to the distance between cells vector
         * 
         * @return const std::vector< std::vector<f32> >& Self-explanatory
         */
        const std::vector< std::vector<f32> >& getCellsDistance();
};
#endif