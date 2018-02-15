#ifndef PLAYER_H
#define PLAYER_H

#include "BuildingManager.h"
#include "UnitManager.h"
#include "Unit.h"
#include <vector>
#include <Types.h>

class Player {
    public:
        Player();
        virtual ~Player();

        void Init();
        virtual void Update() = 0;
        virtual void CleanUp() = 0;

        // Control methods
        void gainResources();
        void spendResources(i32, i32);
        void increaseHappiness(i32);
        void decreaseHappiness(i32);
        void increaseCityLevel(i32);
        void increaseCitizens(i32);
        void increaseArmySize();
        void increaseBuildableRange();
        bool losingBattle(); //ToDo: battle manager mejor no?
        void decreaseBuildings(Enumeration::BuildingType);
        void increaseArmyLevel(i32);
        void decreaseArmyLevel(i32);

        // Setters
        void setHallPosition(Vector3<f32>);
        void setMetalAmount(i32);
        void setCrystalAmount(i32);
        void setSiderurgyProductivity(i32);
        void setQuarryProductivity(i32);



        // Getters
        i32 getHappiness();
        i32 getCityLevel();
        i32 getCitizens();
        i32 getArmySize();
        i32 getMetalAmount();
        i32 getCrystalAmount();
        i32 getMetalProduction();
        i32 getCrystalProduction();
        i32 getArmyLevel();
        BuildingManager* getBuildingManager();
        UnitManager* getUnitManager();
        Vector3<f32> getHallPosition();

        // Tricks
        void receiveMetal();
        void receiveCrystal();
        void receiveCitizens();

    protected:
        // Resources
        i32 happiness;
        i32 cityLevel;
        i32 armyLevel;
        i32 siderurgyProductivity;
        i32 quarryProductivity;
        i32 metalAmount;
        i32 crystalAmount;
        i32 citizens;

        // Army
        bool underAttack;
        
        f32 updateTimer;
        //Buildings
        f32 buildableRange;
        
        //Managers
        BuildingManager *buildings;
        UnitManager *units;

        //City Hall
        Vector3<f32> hallPosition;
    private:
        
};

#endif