#ifndef PLAYER_H
#define PLAYER_H



class Player {
    
public:
        void update();

        Player();
        virtual ~Player();

        //Getters
        int getHappiness();
        int getCityLevel();

        int getMetalProduction();
        int getCrystalProduction();

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

        /////////////////////////////////

        void increaseHappiness(int h);
        void increaseCityLevel(int lvl);

        void increaseSiderurgyAmount();
        void increaseQuarryAmount();

        void increaseCitizens();

        void increaseArmySize();

        void increaseMeleeAmount();
        void increaseRangeAmount();
        void increaseSiegeAmount();

        void buildBarrack();
        void buildBarn();
        void buildWorkshop();

        void increaseWallAmount();
        void increaseTowerAmount();
        //Setters

        protected:
        // Resources
        int happiness;
        int cityLevel;

        int siderurgyAmount;
        int metalProduction;

        int quarryAmount;
        int crystalProduction;

        int citizens;
        // Army
        int armySize;

        int meleeAmount;
        int rangeAmount;
        int siegeAmount;
        int catapultAmount;
        int ramAmount;

        int wallAmount;
        int towerAmount;

        bool wallBuilt;
        bool barrackBuilt;
        bool barnBuilt;
        bool workshopBuilt;
        
        private:
};

#endif