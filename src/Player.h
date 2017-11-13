class Player {
    
    public:
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

        //Setters

    private:
        int happiness;
        int cityLevel;
        int metalProduction;
        int crystalProduction;
        int citizens;
        int armySize;
        int meleeAmount;
        int rangeAmount;
        int siegeAmount;
        int ramAount;
        int catapultAmount;
        bool wallBuilt;
        bool barrackBuilt;
        bool barnBuilt;
        bool workshopBuilt;
        
};