#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include "Unit.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <GraphicEngine/Terrain.h>
#include <Types.h>

class UnitManager{
    public:
        UnitManager(Enumeration::Team teamData, Enumeration::BreedType raceData);
        virtual ~UnitManager();

        void testRaycastCollisions();

        void updateUnitManager();

        //Call for creating new troops, see the .cpp for more info on how to insert the desired unit
        bool createTroop(Enumeration::UnitType unitData);
        void deployTroopAtPosition(i32 index, Vector3<f32> vectorData);
        void startDeployingTroop(i32 index);
        void deployTroop();
        void deployAllTroops(Vector3<f32> vectorData);
        void retractAllTroops(Vector3<f32>);

        bool isTroopSelected();
        void unSelectTroop();
        void moveOrder();
        void selectTroop(i32 troopID);
        void startBattle(i32 enemyID);
        void deleteUnit(i32);

        bool isSolvent(i32, i32);
        bool checkCanPay(Enumeration::UnitType);

        i32 getTotalTroops(); 
		i32 getCollisionID();
        i32 getTroopAmount(Enumeration::UnitType);
        Unit* getSelectedTroop();
        std::map<i32, Unit*> * getInMapTroops();
        std::vector<Unit*> * getInHallTroops();
		std::string getCollisionName();
    private:
        Enumeration::Team team;
        Enumeration::BreedType breed;

        SceneNode *unitLayer;

		SceneNode *currentCollision;

        std::vector<Unit*> *inQueueTroops;
        std::vector<Unit*> *inHallTroops;
        std::map<i32, Unit*> *inMapTroops;

        std::vector<Unit*> *totalTroops;

        Unit *selectedTroop;

        bool isDeployingTroop;
        i32 currentDeployingTroop;

        i32 gridAlignment;
        
        i32 troopsAmount[Enumeration::UnitType::TroopsSize];
};

#endif