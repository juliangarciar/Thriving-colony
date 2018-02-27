#ifndef QUADTREE_H
#define QUADTREE_H
#include <vector>
#include <Types.h>
#include <MathEngine/Vector2.h>
#include <MathEngine/Box2D.h>

class Cell;
class Building;
class Quadtree{
    private:
        Vector2<f32> position;
        Box2D hitBox;
        std::vector<Quadtree*> innerTrees;
        std::vector<Cell*> innerCells;
        i32 deep;
    public:
        /**
         * @brief Default constructor
         * 
         * @param positionData Positon where the quadTree is constructed around 
         * @param hitboxData The hitbos that represents the quadTree collision
         * @param deepValue Represent the k layer where the quadTree is allocated
         */
        Quadtree(Vector2<f32> positionData, Box2D hitboxData, i32 deepValue);
        /**
         * @brief Default destructor
         * 
         */
        ~Quadtree();
        /**
         * @brief Clears the quadtree for a new game
         * 
         */
        void Clear();
        /**
         * @brief Insert the cell in the corresponding quadtree (called from WorldGeometry only)
         * 
         * @param cellPtr Pointer to the cell
         */
        void insertCell(Cell* cellPtr);
        /**
         * @brief Copy the buildingPtr into the cells that collides with its hitbox
         * 
         * @param buildingPtr Pointer to the building
         */
        void insertBuilding(Building* buildingPtr);
        /**
         * @brief Assign each cell his neighbors, by checking the hitbox (really slow method)
         * 
         * @param cellPtr The cell to be assigned his neighbors
         */
        void assignNeighbors(Cell* cellPtr);
        /**
         * @brief Checks if a given hitbox collides with others already inserted
         * 
         * @param otherHitbox The hitbox to be compared with (can be a Unit, either a Building)
         * @return true If collides
         * @return false Else
         */
        bool canBuild(Box2D otherHitbox);
        /**
         * @brief Returns a reference to the hitbox of the quadtree
         * 
         * @return Box2D& 
         */
        Box2D getHitbox();
        /**
         * @brief Returns a Vector2 that indicates the position(center) of the Quadtree
         * 
         * @return Vector2<f32>
         */
        Vector2<f32> getPosition();
};
#endif