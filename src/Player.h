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

        //Setters

    private:
        int happiness;
        int cityLevel;
        int metalProduction;
        int crystalProduction;
        int citizens;
        int armySize;
        int meleeAmount;
        
};