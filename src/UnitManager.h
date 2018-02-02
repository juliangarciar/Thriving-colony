#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include <iostream>
#include <vector>
#include <map>
#include <GraphicEngine/Terrain.h>
#include "Unit.h"
class UnitManager{
    // POR QUE ESTA CLASE ESTA DEL REVES WTF?
    private:
        SceneNode *unitLayer;

		SceneNode *currentCollision;

        std::vector<Unit*> *inHallTroops;
        std::map<int, Unit*> *inMapTroops;

        //std::vector<Unit*> *totalTroops;

        Unit *selectedTroop;

        Enumeration::Team teamManager;
        Enumeration::BreedType breedType;

        bool isDeployingTroop;
        int currentDeployingTroop;

        int gridAlignment;
        
    public:
        UnitManager(Enumeration::Team teamData, Enumeration::BreedType raceData);             //Constructor
        virtual ~UnitManager();                 //Destroyer

        void testRaycastCollisions();
		int getCollisionID();
		std::string getCollisionName();

        void updateUnitManager();               //Updates the UnitManager

        //Call for creating new troops, see the .cpp for more info on how to insert
        //the desired unit
        bool createTroop(Enumeration::UnitType unitData);

        void deployTroopAtPosition(int index, Vector3<float> vectorData);
        void startDeployingTroop(int index);
        void deployTroop(Terrain *terrain);
        void deployAllTroops(Vector3<float> vectorData);

        void retractAllTroops(Vector3<float>);

        void selectTroop(int troopID);      //Call for selecting a troop
        void unSelectTroop();
        void moveOrder(Terrain *terrain);                        //Order for selected troop
        void startBattle(int enemyID);

        void deleteUnit(int);

        bool isSolvent(int, int, Enumeration::Team);
        bool checkCanPay(Enumeration::UnitType);

        int getTotalTroops(); //Returns troop size

        bool isTroopSelected();

        std::map<int, Unit*> * getInMapTroops();
        std::vector<Unit*> * getInHallTroops();
        Unit* getSelectedTroop();
};

#endif