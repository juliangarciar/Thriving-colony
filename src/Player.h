#ifndef PLAYER_H
#define PLAYER_H

#include "BuildingManager.h"
#include "UnitManager.h"
#include "Unit.h"
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

        int getMetalAmount();
        int getCrystalAmount();

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

        bool getUnderAttack();

        //std::vector<Unit*> * getTroops(); //ToDo: lo del cpp

        bool losingBattle();

        BuildingManager* getBuildingManager();
        UnitManager* getUnitManager();
        //Setters
        void setBarnBuilt(bool);
        void setBarrackBuilt(bool);
        void setWorkshopBuilt(bool);

        /////////////////////////////////
        virtual void update() = 0;

        void gainResources();

        void increaseHappiness(int h);
        void increaseCityLevel(int lvl);

        void increaseSiderurgyAmount();
        void increaseQuarryAmount();

        void increaseCitizens();

        void increaseArmySize();

        void increaseMeleeAmount();
        void increaseRangeAmount();
        void increaseSiegeAmount();

        void increaseBarrackAmount();
        void increaseBarnAmount();
        void increaseWorkshopAmount();
        
        void increaseWallAmount();
        void increaseTowerAmount();

        void deployTroops();
        void retractTroops();
        void closeDoors();
        void openDoors();

        void increaseRamAmount();
        void increaseCatapultAmount();

        void increaseBuildableRange();

        void spendResources(int, int);

        void receiveMetal();
        void receiveCrystal();
        void receiveCitizens();

        void decreaseBuildings(Enumeration::BuildingType);

    protected:
        float updateTimer;
        // Resources
        int happiness;
        int cityLevel;
        int metalAmount;
        int crystalAmount;
        int citizens;

        // Army
        int armySize;

        int meleeAmount;
        int rangeAmount;
        int siegeAmount;
        int catapultAmount;
        int ramAmount;

        //Buildings
        //Resource
        int siderurgyAmount;
        int quarryAmount;
        //Military       
        bool barrackBuilt;
        bool barnBuilt;
        bool workshopBuilt;
        int barrackAmount;
        int barnAmount;
        int workshopAmount;

        bool wallBuilt;
        int wallAmount;
        int towerAmount;
        
        bool underAttack;
        
        BuildingManager *buildings;
        UnitManager *units;
        float buildableRange;

    private:
        
};

#endif