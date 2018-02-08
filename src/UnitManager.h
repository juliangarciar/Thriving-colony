#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include "Unit.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <map>
#include <Types.h>
#include <GraphicEngine/Terrain.h>
#include <SoundEngine/SoundSystem.h>
#include <PathPlanner/PathManager.h>

class UnitManager{
    public:
        UnitManager(Enumeration::Team teamData, Enumeration::BreedType raceData);
        virtual ~UnitManager();

        bool createTroop(Enumeration::UnitType unitData);
        void startDeployingTroop(i32 index);
        void deploySelectedTroop(Vector3<f32>);
        void deployAllTroops(Vector3<f32>);
        void retractAllTroops();

        void testRaycastCollisions();
        void updateUnitManager();

        void unSelectTroop();
        void moveOrder();
        void selectTroop(i32 troopID);
        void startBattle(i32 enemyID);
        void deleteUnit(i32);

        bool isTroopSelected();
        bool isSolvent(i32, i32);
        bool checkCanPay(Enumeration::UnitType);
        bool isDeployingTroop();
        bool areTroopsDeployed();
        void enterMainBuilding(Enumeration::UnitType);

        //SETTER
        Unit* setNewUnitModel(Enumeration::UnitType);

        //GETTERS
		i32 getCollisionID();
        i32 getTroopAmount(Enumeration::UnitType);
        i32 getTotalTroopAmount();
        i32 getDeployingTroopID();
        Unit* getSelectedTroop();
        std::map<i32, Unit*> *getInQueueTroops();
        std::map<i32, Unit*> *getInHallTroops();
        std::map<i32, Unit*> *getInMapTroops();
		std::string getCollisionName();
    private:
        Enumeration::Team team;
        Enumeration::BreedType breed;

        SceneNode *unitLayer;
		SceneNode *currentCollision;

        std::map<i32, Unit*> *inQueueTroops;
        std::map<i32, Unit*> *inHallTroops;
        std::map<i32, Unit*> *inMapTroops;

        Unit *selectedTroop;

        bool deployingTroop;
        i32 currentDeployingTroop;
        
        i32 troopsAmount[Enumeration::UnitType::TroopsSize];

        i32 nextTroopId;

        i32 gridAlignment;
};

#endif