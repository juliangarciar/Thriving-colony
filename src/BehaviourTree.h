#include "IA.h"

class BehaviourTree{
    public:
        BehaviourTree();
        ~BehaviourTree();
        virtual void makeChoice();
        float calculateMetalProductionRate();
        float calculateCrystalProductionRate();
        float calculateCitizensRate();
        float calculateArmyCitizensRate();
        float calculateMeleeRate();

    protected:
        IA* ia;
        int happinessThreshold;
        int quarryMilestone;
        int mountedCriatureMilestone;
        int wallMilestone;
        float metalThreshold;
        float crystalThreshold;
        float citizensThreshold;
        float armyThreshold;
        float meleeThreshold;

    private:
        
};