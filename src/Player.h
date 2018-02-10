#ifndef PLAYER_H
#define PLAYER_H

#include "BuildingManager.h"
#include "UnitManager.h"
#include "Unit.h"
#include <vector>
#include <Types.h>

//ToDo: no se si deberia ir aqui
#define RESOURCEPRODUCTION 10

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
        void increaseHappiness(i32 h);
        void decreaseHappiness(i32);
        void increaseCityLevel(i32 lvl);
        void increaseCitizens(i32 c);
        void increaseArmySize();
        void increaseBuildableRange();
        bool losingBattle(); //ToDo: battle manager mejor no?
        void decreaseBuildings(Enumeration::BuildingType);

        // Setters
        void setHallPosition(Vector3<f32>);

        // Getters
        i32 getHappiness();
        i32 getCityLevel();
        i32 getCitizens();
        i32 getArmySize();
        i32 getMetalAmount();
        i32 getCrystalAmount();
        i32 getMetalProduction();
        i32 getCrystalProduction();
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