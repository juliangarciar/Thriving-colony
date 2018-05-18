#ifndef PLAYER_H
#define PLAYER_H

#include "BuildingManager.h"
#include "UnitManager.h"
#include "Unit.h"
#include <vector>
#include <Types.h>
#include <IOEngine/Timer.h>

/**
 * @class Player.
 * @brief Create a Player type object.
 */
class Player {
    
    public:
        /**
         * @brief Player constructor.
         */
        Player();

        /**
         * @brief Player destructor.
         */
        virtual ~Player();

        /**
         * @brief Initialize the variables.
         */
        void Init();

        /**
         * @brief Virtual method that will be implemented at classes that will inherit from Player class.
         * 
         * @see Update() method from Human class.
         * @see Update() method from IA class.
         */
        virtual void Update() = 0;

        /**
         * @brief Virtual method that will be implemented at classes that will inherit from Player class.
         * 
         * @see CleanUp() method from Human class.
         * @see CleanUp() method from IA class.
         */
        virtual void CleanUp() = 0;

        /**
         * @brief Increase the metal and crystal amount based on the production of each one.
         */
        void gainResources();

        /**
         * @brief Decrease the metal and crystal amount based on the meatl and rystal cost passed by parameter.
         * 
         * @param metalCost is the amount that is going to be subtracted from metalAmount variable.
         * @param crystalCost is the amount that is going to be subtracted from crystalAmount variable.
         */
        void spendResources(i32 metalCost, i32 crystalCost);

        /**
         * @brief Increase the happiness of the player's city based on the happiness passed by parameter.
         * 
         * @param i32 is the happiness that is going to be added to happiness variable. Can be a negative number.
         */
        void increaseHappiness(i32);

        /**
         * @brief Decrease the happiness of the player's city based on the happiness passed by parameter.
         * 
         * @param i32 is the happiness that is going to be subtracted to happiness variable. Can be a negative number.
         */
        void decreaseHappiness(i32);

        /**
         * @brief Increase the city level based on the city level passed by parameter.
         * 
         * @param i32 is the city level that is going to be added to cityLevel variable. 
         */
        void increaseCityLevel(i32);

        /**
         * @brief Increase the citizens based on the citizens passed by parameter.
         * 
         * @param i32 is the citizens that are going to be added to citizens variable.
         */
        void increaseCitizens(i32);

        /**
         * @brief Increase the people based on the people passed by parameter.
         * 
         * @param i32 is the people that are going to be added to the people variable.
         */
        void increasePeople(i32);

        /**
         * @brief Increase the individual units based on the individual units passed by parameter.
         * 
         * @param i32 is the units that are going to be added to the individualUnits variable.
         */
        void increaseIndividualUnits(i32);

        /**
         * @brief Decrease the people based on the persosns passed by parameter.
         * 
         * @param i32 is the people that are going to be substracted to the people variable.
         */
        void decreasePeople(i32);

        /**
         * @brief Decrease the individualU units based on the individual units passed by parameter.
         * 
         * @param i32 is the units that are going to be substracted to the individualUnits variable.
         */
        void decreaseIndividualUnits(i32);

        /**
         * @brief Decrease 10 citizens and 5 happiness from the player's city.
         */
        void increaseArmySize();

        /**
         * @brief Increases the range where the player can build.
         */
        void increaseBuildableRange();

        /**
         * @brief Determinate if the palyer is loosing the battle.
         * 
         * @return True if the player is loosing the battle and false in other case.
         */
        bool losingBattle(); //ToDo: battle manager mejor no?

        /**
         * @brief Increase the player's amry level based on the level passed by parameter.
         * 
         * @param i32 is the army level that is going to be added to armyLevel variable.
         */
        void increaseArmyLevel(i32);

        /**
         * @brief Decrease the palyer's army level based on the level passed by parameter.
         * 
         * @param i32 is the army level that is going to be subtracted to armyLevel variable.
         */
        void decreaseArmyLevel(i32);

        /**
         * @brief Set the position of the player's command center.
         * 
         * @param Vector2 is the value that is going to be assigned to hallPosition variable.
         */
        void setHallPosition(Vector3<f32>);

        /**
         * @brief Set the palyer's metal amount.
         * 
         * @param i32 is the value that is going to be assigned to metalAmount variable.
         */
        void setMetalAmount(i32);

        /**
         * @brief Set the player's crystal amount.
         * 
         * @param i32 is the value that is going to be assigned to crystalAmount variable.
         */
        void setCrystalAmount(i32);

        /**
         * @brief Set the production of each siderurgy.
         * 
         * @param i32 is the value that is going to be assigned to siderurgyProductivity variable.
         */
        void setSiderurgyProductivity(i32);

        /**
         * @brief Set the production of each quarry.
         * 
         * @param i32 is the value that is going to be assigned to quarryProductivity variable.
         */
        void setQuarryProductivity(i32);

        /**
         * @brief 
         * 
         * @param i32 is the value that is going to be assigned to buildingRadious variable.
         */
        void setBuildingRadious(f32);

        /**
         * @brief Get the happiness of the player's city.
         * 
         * @return i32 that will be the value of happiness variable.
         */
        i32 getHappiness();

        /**
         * @brief Get the player's city level.
         * 
         * @return i32 that will be the value of cityLevel variable.
         */
        i32 getCityLevel();

        /**
         * @brief Get the player's citizens amount.
         * 
         * @return i32 that will be the value of citizens variable.
         */
        i32 getCitizens();

        /**
         * @brief Get the player's people amount.
         * 
         * @return i32 that will be the value of people varibale.
         */
        i32 getPeople();

        /**
         * @brief Get the player's individualUnits amount.
         * 
         * @return i32 that will be the value of individualUnits varibale.
         */
        i32 getIndividualUnits();

        /**
         * @brief Get the player's troops amount.
         * 
         * @return i32 that will be the total troops amount.
         * @see getTotalTroopAmount() method from UnitManager class.
         */
        i32 getArmySize();

        /**
         * @brief Get the player's metal amount.
         * 
         * @return i32 that will be the value of metalAmount variable.
         */
        i32 getMetalAmount();

        /**
         * @brief Get the player's crystal amount.
         * 
         * @return i32 that will be the value of crystalAmount variable.
         */
        i32 getCrystalAmount();

        /**
         * @brief Get the metal production of the player's city.
         * 
         * @return i32 that will be the total metal amount produced. 
         */
        i32 getMetalProduction();

        /**
         * @brief Get the crystal production of the player's city.
         * 
         * @return i32 that will be the total crystal amount produced.
         */
        i32 getCrystalProduction();

        /**
         * @brief Get the player's army level.
         * 
         * @return i32 that will be the value of armyLevel variable.
         */
        i32 getArmyLevel();

        /**
         * @brief
         * 
         * @return f32 that will be the value of buildingRadious variable.
         */
        f32 getBuildingRadious();

        /**
         * @brief Get the player's buildings.
         * 
         * @return Pointer to a BuildingManager object that will be the value of buildings variable.
         */
        BuildingManager* getBuildingManager();

        /**
         * @brief Get the player's troops.
         * 
         * @return Pointer to a UnitManager object that will be the value of units variable.
         */
        UnitManager* getUnitManager();

        /**
         * @brief Get the position of the player's commamd center.
         * 
         * @return Vector3 that will be the value of hallPosition variable.
         */
        Vector3<f32> getHallPosition();

        /**
         * @brief Add 200 of metal to the player's metal amount.
         */
        void receiveMetal();

        /**
         * @brief Add 100 of crystal to the player's crystal amount.
         */
        void receiveCrystal();

        /**
         * @brief Add 100 citizens to the player's citizens amount.
         */
        void receiveCitizens();

    protected:
        //Happiness of the player's city.
        i32 happiness;

        //Player's city level.
        i32 cityLevel;

        //Player's army level.
        i32 armyLevel;

        //Production of one siderurgy.
        i32 siderurgyProductivity;

        //Production of one quarry.
        i32 quarryProductivity;

        //PLayer's metal amount.
        i32 metalAmount;

        //PLayer's crystal amount.
        i32 crystalAmount;

        //Player's units amount.
        i32 individualUnits;

        //Player's citizens amount.
        i32 citizens;

        //Player's citizens and units maximum amount.
        i32 people;

        //Player's citizens in coming amount.
        i32 citizensInComing;

        //
        i32 buildingRadious;

        //True if player's city is under attack and false in other case.
        bool underAttack;
        
        //Time used to update the variables.
        Timer* updateTimer;

        //
        f32 buildableRange;
        
        //Player's buildings.
        BuildingManager *buildings;

        //PLayer's troops.
        UnitManager *units;

        //Position of the player's command center.
        Vector3<f32> hallPosition;

    private:
        
};

#endif