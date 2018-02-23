#ifndef CELL2_H
#define CELL2_H
#include <vector>
#include <Types.h>
class Box2D;
class Building;
class Unit;
class Vector2;
class Cell{
    private:
        Box2D& hitBox;
        Vector2<f32>& position;
        Building* inhabitingBuilding;
        std::vector<Unit*> inhabitingUnits;
        std::vector<Cell*> neighbors;
        i32 index;
        bool blocked;
    public:
        /**
         * @brief Constructs a cell that represents a portion of the map that knows who's inhabitating him
         * 
         * @param vectorPosition Position of the map where the cell is allocated
         * 
         * @param idx The index of the cell (only called from the WorldGeometry)
         * 
         * @param halfisze Halfisze of the total size of a cell (only called from the WorldGeometry)
         */
        Cell(Vector2<f32>& vectorPosition, i32 idx, i32 halfsize);
        /**
         * @brief Standard destructor
         * 
         */
        ~Cell();
        /**
         * @brief Gives the cell a pointer of a building which is colliding with the cell
         * 
         * @param buildingPtr Pointer of the colliding building
         */
        void setInhabitingBuilding(Building* buildingPtr);
        /**
         * @brief Clears the information about the building inhabiting the cell
         * 
         */
        void clearInhabitingBuilding();
        /**
         * @brief Gives the cell information about the units inhabiting the cell
         * 
         * @param unitPtr Pointer to the unit which enters the cell's area
         */
        void setInhabitingUnit(Unit* unitPtr);
        /**
         * @brief Clears the information about a inhabiting unit in the cell
         * 
         * @param unitPtr Pointer to the unit which is leaving the cell's area
         */
        void clearInhabitingUnit(Unit* unitPtr);
        /**
         * @brief Give the cell information about the cells surrounding the cell
         * 
         * @param cellPtr Pointer to the cell that is next to this cell
         */
        void setNeighbor(Cell* cellPtr);
        /**
         * @brief Set if the cell is transversable or not
         * 
         * @param data 
         */
        void setBlocked(bool data);
        /**
         * @brief Prepares the cell for a new instance of the game, clearing
         * what's inside the cell
         */
        void Clear();
        /**
         * @brief Returns a reference to this cell's hitbox
         * 
         * @return Box2D& 
         */
        Box2D& getHitBox();
        /**
         * @brief Gives information about this cell's position
         * 
         * @return Vector2<f32>& 
         */
        Vector2<f32>& getPosition();
        /**
         * @brief Gives information about the building inhabiting this cell (0 if none)
         * 
         * @return Building* 
         */
        Building* getInhabitingBuilding();
        /**
         * @brief Gives information about the units ihabiting this cell (size == 0 if none)
         * 
         * @return std::vector<Unit*> 
         */
        std::vector<Unit*> getInhabitingUnits();
        /**
         * @brief Gives information about the cells surrounding this cell (3 at least)
         * 
         * @return std::vector<Cell*> 
         */
        std::vector<Cell*> getNeighbors();
        /**
         * @brief Returns the index of the cell (only called from WorldGeometry)
         * 
         * @return i32 
         */
        i32 getIndex();
        /**
         * @brief Returns if the cell is blocked
         * 
         * @return true If it's blocked
         * @return false Else
         */
        bool isBlocked();
        /**
         * @brief Checks if this cell's hitbox collides with the one passed by reference
         * 
         * @param otherHitbox The hitbox which will be compared to the cell's hitbox
         * @return true If collides
         * @return false Else
         */
        bool collides(Box2D& otherHitbox);
};
#endif