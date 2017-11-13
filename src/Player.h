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
        bool wallBuilt;
        bool barrackBuilt;
        bool barnBuilt;
        bool workshopBuilt;
        
};