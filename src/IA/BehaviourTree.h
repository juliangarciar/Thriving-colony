#ifndef BEHAVIOUR_TREE_H
#define BEHAVIOUR_TREE_H

#include "../Player.h"
#include "IA.h"

class BehaviourTree {
    
    public:
        BehaviourTree(IA*);
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

        void debugMessage();

    protected:
        IA* ia;

        int happinessThreshold;
        int quarryMilestone;
        int mountedCreatureMilestone;
        int wallMilestone;
        int towerMilestone;
        int barnMilestone;
        int workshopMilestone;
        int creatureMilestone;

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