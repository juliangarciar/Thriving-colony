#ifndef PLAYER_H
#define PLAYER_H

#include "Melee.h"
#include "Ranged.h"
#include "Building.h"
#include <vector>

class Player {
    
    public:
        Player();
        virtual ~Player();

        //Getters
        int getHappiness();
        int getCityLevel();

        int getMetalProduction();
        int getCrystalProduction();

        int getCitizens();

        int getArmySize();
        int getMeleeAmount();
        int getRangeAmount();
        int getSiegeAmount();
        int getRamAmount();
        int getCatapultAmount();

        bool getWallBuilt();
        bool getBarrackBuilt();
        bool getBarnBuilt();
        bool getWorkshopBuilt();

        int getSiderurgyAmount();
        int getQuarryAmount();

        int getWallAmount();
        int getTowerAmount();

        bool getClosedDoors();
        bool getDeployedTroops();

        bool losingBattle();

        /////////////////////////////////
        void update();

        void increaseHappiness(int h);
        void increaseCityLevel(int lvl);

        void increaseSiderurgyAmount();
        void increaseQuarryAmount();

        void increaseCitizens();

        void increaseArmySize();

        void increaseMeleeAmount();
        void increaseRangeAmount();
        void increaseSiegeAmount();

        void buildBuilding(int, Vector3<float>*, Enumeration::BuildingType, bool);
        void buildTower(int, int, int, Vector3<float>*, bool);

        void increaseWallAmount();
        void increaseTowerAmount();

        static void deployTroops();
        static void retractTroops();
        void closeDoors();
        void openDoors();

        Unit** getTroops();
        //Setters

    protected:
        // Resources
        int happiness;
        int cityLevel;

        int siderurgyAmount;

        int quarryAmount;

        int citizens;
        // Army
        int armySize;

        int meleeAmount;
        int rangeAmount;
        int siegeAmount;
        int catapultAmount;
        int ramAmount;

        int wallAmount;
        int towerAmount;

        bool wallBuilt;
        bool barrackBuilt;
        bool barnBuilt;
        bool workshopBuilt;

        static bool deployedTroops;
        bool closedDoors;
        
        Melee **melees;
        Ranged **rangeds;
        std::vector<Building*> *buildings;

    private:
        
};

#endif