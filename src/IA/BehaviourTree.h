#ifndef BEHAVIOUR_TREE_H
#define BEHAVIOUR_TREE_H

#include "../IA.h"

class BehaviourTree {
    
    public:
        BehaviourTree(/*IA* iaPnt*/);
        ~BehaviourTree();
        void makeChoice();

        virtual void developCity() = 0;
        void serviceBranch();
        void unitsBranch();
        void buildingsBranch();
        void armyBranch();
        void resourcesBranch();

        bool needResourcesInvestment();
        bool needArmyInvestment();
        
        bool evaluateWallNeed();

        virtual bool readyToAttack() = 0;

        float calculateMetalProductionRate();
        float calculateCrystalProductionRate();
        float calculateCitizensRate();
        float calculateArmyCitizensRate();
        float calculateMeleeRate();
        float calculateRangeRate();
        float calculateSiegeRate();

        int getHospitalMilestone();
        int getMarketMilestone();
        int getQuarryMilestone();
        
        int getCreatureMilestone();
        int getMountedCreatureMilestone();

        int getHappinessThreshold();

        float getMeleeThreshold();
        float getRangeThreshold();
        float getCitizensThreshold();
        
        

        bool getShortOnCrystal();
        bool getShortOnMetal(); 

        bool getNeedSoldiers();
        bool getNeedBuildings();

        bool getNeedBarracks();
        bool getNeedBarn();
        bool getNeedWorkshop();
        bool getNeedWall();
        bool getNeedTower();

        void debugMessage();

    protected:

        int happinessThreshold;
        int quarryMilestone;
        int mountedCreatureMilestone;
        int wallMilestone;
        int towerMilestone;
        int barnMilestone;
        int workshopMilestone;
        int creatureMilestone;

        int hospitalMilestone;
        int marketMilestone;

        float metalThreshold;
        float crystalThreshold;
        float citizensThreshold;
        float armyThreshold;
        float meleeThreshold;
        float rangeThreshold;
        float siegeThreshold;

        bool underAttack;
        // The production rate of a given resource is low in comparison with your city level
        bool shortOnMetal;
        bool shortOnCrystal;

        bool needSoldiers;
        // Dictate the need of a certain building
        bool needBarracks;
        bool needBarn;
        bool needWorkshop;
        bool needWall;
        bool needTower;
        // Dictate the requirement of a certain building
        bool requireBarracks;
        bool requireBarn;
        bool requireWorkshop;

    private:
};

#endif