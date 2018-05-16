#ifndef QUADTREE_H
#define QUADTREE_H
#include <vector>
#include <Types.h>
#include <MathEngine/Vector2.h>
#include <MathEngine/Box2D.h>

class Cell;
class Entity;
class Unit;
class Building;
class Quadtree{
    public:
        /**
         * @brief Default constructor
         * 
         * @param positionData Positon where the quadTree is constructed around 
         * @param hitboxData The hitbos that represents the quadTree collision
         * @param deepValue Represent the k layer where the quadTree is allocated
         */
        Quadtree(Vector2<f32> positionData, const Box2D& hitboxData, i32 deepValue);
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
        bool checkCollision(const Box2D& otherHitbox) const;
        /**
         * @brief Returns a reference to the hitbox of the quadtree
         * 
         * @return Box2D& 
         */
        const Box2D& getHitbox() const;
        /**
         * @brief Returns a Vector2 that indicates the position(center) of the Quadtree
         * 
         * @return Vector2<f32>
         */
        const Vector2<f32> getPosition() const;

        void getCollidingEntities(const Box2D& hitbox, std::vector< Entity* >& collidingEntities, std::vector< Unit* >& flockingUnits) const;
    private:
        const Vector2<f32> position;
        const Box2D hitBox;
        std::vector<Quadtree*> innerTrees;
        std::vector<Cell*> innerCells;
        const i32 depth;
};
#endif