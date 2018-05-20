#ifndef CELL_H
#define CELL_H

#include <vector>
#include <Types.h>
#include <MathEngine/Vector2.h>
#include <MathEngine/Box2D.h>

class Building;

class Unit;

class Cell{

    public:
        /**
         * @brief Constructs a cell that represents a portion of the map that knows who's inhabitating him
         * 
         * @param vectorPosition The position where the cell is consctructed around
         * @param hitboxData The hitbos that represents the cell collision
         * @param idx Index given by the worldGeometry array in order to fast acces 
         */
        Cell(Vector2<f32> vectorPosition, const Box2D& hitboxData, i32 idx);

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
         * @param data True if represents a blocked portion of the map, false else
         */
        void setBlocked(bool data);

        /**
         * @brief Prepares the cell for a new instance of the game, clearing what's inside this
         */
        void Clear();

        /**
         * @brief Returns a reference to this cell's hitbox
         * 
         * @return Box2D& 
         */
        const Box2D& getHitbox() const;

        /**
         * @brief Gives information about this cell's position
         * 
         * @return Vector2<f32> 
         */
        Vector2<f32> getPosition() const;

        /**
         * @brief Gives information about the building inhabiting this cell (0 if none)
         * 
         * @return Building* 
         */
        Building* getInhabitingBuilding() const;

        /**
         * @brief Gives information about the units ihabiting this cell (size == 0 if none)
         * 
         * @return std::vector<Unit*>&
         */
        const std::vector<Unit*>& getInhabitingUnits();

        /**
         * @brief Gives information about the cells surrounding this cell (3 at least)
         * 
         * @return std::vector<Cell*>& 
         */
        const std::vector<Cell*>& getNeighbors() const;

        /**
         * @brief Returns the index of the cell (only called from WorldGeometry)
         * 
         * @return i32 
         */
        i32 getIndex() const;

        /**
         * @brief Returns if the cell is blocked
         * 
         * @return true If it's blocked
         * @return false Else
         */
        bool isBlocked() const;
        
        /**
         * @brief Checks if this cell's hitbox collides with the one passed by reference
         * 
         * @param otherHitbox The hitbox which will be compared to the cell's hitbox
         * @return true If collides
         * @return false Else
         */
        bool collides(const Box2D& otherHitbox) const;

        i32 getTotalInhabitingUnits() const;
    private:
        Vector2<f32> position;
        Box2D hitBox;
        i32 index;
        Building* inhabitingBuilding;
        std::vector<Unit*> inhabitingUnits;
        std::vector<Cell*> neighbors;
        bool blocked;
};

#endif