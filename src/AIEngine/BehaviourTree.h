#ifndef BEHAVIOUR_TREE_H
#define BEHAVIOUR_TREE_H

#include <Types.h>

class BehaviourTree {
    
    public:
        BehaviourTree();
        virtual ~BehaviourTree();
        void makeChoice();
/*
        void serviceBranch();
        void unitsBranch();
        void buildingsBranch();
        void armyBranch();
        void resourcesBranch();
*/
        bool needResourcesInvestment();
        bool needArmyInvestment();
        
        bool evaluateWallNeed();

        bool readyToAttack();

        f32 calculateMetalProductionRate();
        f32 calculateCrystalProductionRate();
        f32 calculateCitizensRate();
        f32 calculateArmyCitizensRate();
        f32 calculateMeleeRate();
        f32 calculateRangeRate();
        f32 calculateSiegeRate();

        i32 getHospitalMilestone();
        i32 getMarketMilestone();
        i32 getQuarryMilestone();
        
        i32 getCreatureMilestone();
        i32 getMountedCreatureMilestone();

        i32 getHappinessThreshold();
        i32 getAttackThreshold();

        f32 getMeleeThreshold();
        f32 getRangeThreshold();
        f32 getCitizensThreshold();

        bool getShortOnCrystal();
        bool getShortOnMetal(); 

        bool getNeedSoldiers();
        bool getNeedBuildings();

        bool getNeedBarracks();
        bool getNeedBarn();
        bool getNeedWorkshop();
        bool getNeedWall();
        bool getNeedTower();
        
        bool getUnderAttack();

        //Goal oriented
        bool getRequireBarrack();
        bool getRequireBarn();
        bool getRequireWorkshop();

        void setRequireBarrack(bool);
        void setRequireBarn(bool);
        void setRequireWorkshop(bool);

        void setRequireCrystal(bool);
        bool getRequireCrystal();

        void setRequireCitizens(bool);
        bool getRequireCitizens();

        void init(i32);

        i32 getBarracks();
        i32 getBarns();
        i32 getWorkshops();

        void addBarrack();
        void addBarn();
        void addWorkshop();

        i32 quarryMilestone;
        i32 mountedCreatureMilestone;
        i32 wallMilestone;
        i32 towerMilestone;
        i32 barnMilestone;
        i32 workshopMilestone;
        i32 creatureMilestone;
    protected:
        i32 happinessThreshold;
        i32 attackThreshold;

        i32 hospitalMilestone;
        i32 marketMilestone;

        f32 metalThreshold;
        f32 crystalThreshold;
        f32 citizensThreshold;
        f32 armyThreshold;
        f32 meleeThreshold;
        f32 rangeThreshold;
        f32 siegeThreshold;

        i32 barracks;
        i32 barns;
        i32 workshops;

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
        bool requireBarrack;
        bool requireBarn;
        bool requireWorkshop;

        bool requireCrystal;

        bool requireCitizens;

    private:
};

#endif