#ifndef BEHAVIOUR_TREE_H
#define BEHAVIOUR_TREE_H

#include "IA.h"

class BehaviourTree {
    
    public:
        BehaviourTree(IA*);
        ~BehaviourTree();
        void makeChoice();

        virtual void developCity() = 0;
        void serviceBranch();
        void unitsBranch();

        virtual bool readyToAttack() = 0;

        float calculateMetalProductionRate();
        float calculateCrystalProductionRate();
        float calculateCitizensRate();
        float calculateArmyCitizensRate();
        float calculateMeleeRate();
        float calculateRangeRate();
        float calculateSiegeRate();

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

    private:
        
};

#endif