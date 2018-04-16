#ifndef UNITMANAGER_H
#define UNITMANAGER_H

#include "Unit.h"
#include <cstdlib>
#include <vector>
#include <map>
#include <Types.h>
#include <GraphicEngine/Terrain.h>
#include <SoundEngine/SoundSystem.h>
#include <PathPlanner/PathManager.h>

class UnitManager{
    public:
        UnitManager(Enumeration::Team, std::string);
        virtual ~UnitManager();

        bool createTroop(std::string unitData);
        void startDeployingTroop(i32 troopID);
        void deploySelectedTroop(Vector2<f32>);
        void startDeployingAllTroops();
        void deployAllTroops(Vector2<f32>);
        void retractAllTroops();

        void testRaycastCollisions();
        void updateUnitManager();

        void unSelectTroop();
        void moveOrder();
        void selectTroop(i32 troopID);
        void startBattle(i32 enemyID);
        void deleteUnit(i32);

        bool isTroopSelected();
        bool isSolvent(i32, i32, i32);
        bool checkCanPay(std::string);
        bool isDeployingTroop();
        bool areTroopsDeployed();
        bool areTroopsInMap();

        //GETTERS
		i32 getCollisionID();
        i32 getTroopAmount(std::string);
        i32 getTotalTroopAmount();
        i32 getDeployingTroopID();
        Unit* getSelectedTroop();
        std::map<i32, Unit*> *getInQueueTroops();
        std::map<i32, Unit*> *getInHallTroops();
        std::map<i32, Unit*> *getInMapTroops();
		std::string getCollisionName();
    private:
        Enumeration::Team team;

        SceneNode *unitLayer;
		SceneNode *currentCollision;

        std::map<std::string, UnitData> baseUnits;

        std::map<i32, Unit*> *inQueueTroops;
        std::map<i32, Unit*> *inHallTroops;
        std::map<i32, Unit*> *inMapTroops;

        std::map<std::string, i32> troopsAmount;

        Unit *selectedTroop;

        bool deployingTroop;
        i32 currentDeployingTroop;

        i32 nextTroopId;

        //i32 gridAlignment;
};

#endif