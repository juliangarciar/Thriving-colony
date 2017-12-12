#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include <iostream>
#include <vector>
#include "Unit.h"
class UnitManager{
    private:
        std::vector < Unit* > totalTroops;
        Unit *selectedTroop;
    public:
        UnitManager();                          //Constructor
        virtual ~UnitManager();                 //Destroyer

        std::vector < Unit* > getTotalTroops(); //Returns all troops player has
        
        void updateUnitManager();               //Updates the UnitManager
        void createTroop();                     //Call for creating new troops
        void selectTroop(Unit *troopData);      //Call for selecting a troop
        void newOrder();                        //Order for selected troop
};

#endif