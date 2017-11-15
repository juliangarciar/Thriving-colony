#include "IA.h"

class BehaviourTree {
    
    public:
        BehaviourTree(IA*);
        ~BehaviourTree();
        virtual void makeChoice();

        virtual void developCity();
        void serviceBranch();
        void militaryBranch();

        virtual bool readyToAttack();

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