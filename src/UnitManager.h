#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include <iostream>
#include <vector>
#include "Ranged.h"
#include "Melee.h"
class UnitManager{
    // POR QUE ESTA CLASE ESTA DEL REVES WTF?
    private:
        std::vector<Unit*> *inHallTroops;
        std::vector<Unit*> *inMapTroops;

        std::vector<Unit*> *totalTroops;

        Unit *selectedTroop;

        Enumeration::Team teamManager;
    public:
        UnitManager(Enumeration::Team teamData);             //Constructor
        virtual ~UnitManager();                 //Destroyer

        std::vector<Unit*> *getTotalTroops(); //Returns all troops player has
        void updateUnitManager();               //Updates the UnitManager

        //Call for creating new troops, see the .cpp for more info on how to insert
        //the desired unit
        void createTroop(Vector3<float> *vectorData, Enumeration::UnitType unitData);
        void deployTroop(int index);
        void selectTroop(Unit *troopData);      //Call for selecting a troop
        void newOrder();                        //Order for selected troop

        bool isSolvent(int, int, Enumeration::Team);
        bool checkCanPay(Enumeration::UnitType::SubClass);
};

#endif