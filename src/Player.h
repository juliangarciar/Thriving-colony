#ifndef PLAYER_H
#define PLAYER_H

#include "BuildingManager.h"
#include "UnitManager.h"
#include "Unit.h"
#include <vector>

//ToDo: no se si deberia ir aqui
#define RESOURCEPRODUCTION 10

class Player {
    public:
        Player();
        virtual ~Player();

        virtual void update() = 0;

        // Control methods
        void gainResources();
        void spendResources(int, int);
        void increaseHappiness(int h);
        void decreaseHappiness(int);
        void increaseCityLevel(int lvl);
        void increaseCitizens(int c);
        void increaseArmySize();
        void increaseBuildableRange();
        bool losingBattle(); //ToDo: battle manager mejor no?

        // Getters
        int getHappiness();
        int getCityLevel();
        int getCitizens();
        int getArmySize();
        int getMetalAmount();
        int getCrystalAmount();
        int getMetalProduction();
        int getCrystalProduction();
        BuildingManager* getBuildingManager();
        UnitManager* getUnitManager();

        // Tricks
        void receiveMetal();
        void receiveCrystal();
        void receiveCitizens();

        void decreaseBuildings(Enumeration::BuildingType);

    protected:
        // Resources
        int happiness;
        int cityLevel;
        int metalAmount;
        int crystalAmount;
        int citizens;

        // Army
        bool underAttack;
        
        //Buildings
        float buildableRange;
        
        //Managers
        BuildingManager *buildings;
        UnitManager *units;

        //City Hall
        Vector3<f32> hallPosition;
    private:
        
};

#endif