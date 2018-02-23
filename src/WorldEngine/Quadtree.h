#ifndef QUADTREE_H
#define QUADTREE_H
#include <vector>
#include <Types.h>
class Cell;
class Box2D;
class Vector2;
class Quadtree{
    private:
        Box2D& hitBox;
        std::vector<Quadtree*> innerTrees;
        std::vector<Cell*> innerCells;
        i32 deep;
    public:
        /**
         * @brief Default constructor
         * 
         * @param position The position where the center of the queadtree resides
         * @param length The lenght of the hitbox
         * @param width The width of the hitbox
         * @param deepValue Number of layers (0 indicates the layer where the cells inhabit)
         */
        Quadtree(Vector2<f32>& position, i32 length, i32 width, i32 deepValue);
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
        bool insertCell(Cell* cellPtr);
        /**
         * @brief Checks if a given hitbox collides with others already inserted
         * 
         * @param otherHitbox The hitbox to be compared with (can be a Unit, either a Building)
         * @return true If collides
         * @return false Else
         */
        bool canBuild(Box2D& otherHitbox);
        /**
         * @brief Returns the hitbox of the quadtree
         * 
         * @return Box2D& 
         */
        Box2D& getHitbox();
};
#endif