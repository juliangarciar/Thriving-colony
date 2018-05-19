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
         * @brief Updates the resistance and the damage of the palyer's troops.
         * 
         * @see Update() method from Human class.
         * @see Update() method from IA class.
         */
        void Update();

        /**
         * @brief Virtual method that will be implemented at classes that will inherit from Player class.
         * 
         * @see CleanUp() method from Human class.
         * @see CleanUp() method from IA class.
         */
        void CleanUp();

        /**
         * @brief updates the metal and crystal amount based on the production of each one.
         */
        void updateResources();

        /**
         * @brief Decrease the metal and crystal amount based on the meatl and rystal cost passed by parameter.
         * 
         * @param metalCost is the amount that is going to be subtracted from metalAmount variable.
         * @param crystalCost is the amount that is going to be subtracted from crystalAmount variable.
         */
        void spendResources(i32 metalCost, i32 crystalCost);

        /**
         * @brief increase the range where the player can build.
         */
        void increaseBuildableRange();

		/**
		 * @brief 
		 * @param metal cost
		 * @param crystal cost
		 * @param citizen cost
		 */
		bool isSolvent(i32, i32, i32);

        /**
         * @brief Modify the happiness of the player's city based on the happiness passed by parameter.
         * 
         * @param i32 is the happiness that is going to be added to happiness variable. Can be a negative number.
         */
        void modifyHappiness(i32);

        /**
         * @brief modify the citizens based on the citizens passed by parameter.
         * 
         * @param i32 is the citizens that are going to be added to citizens variable.
         */
        void modifyCitizens(i32);

        /**
         * @brief modify the max people based on the people passed by parameter.
         * 
         * @param i32 is the people that are going to be added to the people variable.
         */
        void modifyMaxPeople(i32);

        /**
         * @brief modify the city level based on the city level passed by parameter.
         * 
         * @param i32 is the city level that is going to be added to cityLevel variable. 
         */
        void modifyCityLevel(i32);

        /**
         * @brief modify the player's amry level based on the level passed by parameter.
         * 
         * @param i32 is the army level that is going to be added to armyLevel variable.
         */
        void modifyArmyLevel(i32);

        /**
         * @brief Get the player's troops amount.
         * 
         * @return i32 that will be the total troops amount.
         * @see getTotalTroopAmount() method from UnitManager class.
         */
        i32 getArmySize();

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
		 * @brief Get the Happiness
		 * 
		 * @return i32 
		 */
		i32 getHappiness();

		/**
		 * @brief Get the Citizens
		 * 
		 * @return i32 
		 */
		i32 getCitizens();

		/**
		 * @brief Get Max People
		 * 
		 * @return i32 
		 */
		i32 getMaxPeople();

		/**
		 * @brief Get the City Level
		 * 
		 * @return i32 
		 */
		i32 getCityLevel();

		/**
		 * @brief Get the Army Level
		 * 
		 * @return i32 
		 */
		i32 getArmyLevel();

		/**
		 * @brief Get the Resistance Modifier
		 * 
		 * @return i32 
		 */
		i32 getResistanceModifier();

		/**
		 * @brief Get the Damage Modifier
		 * 
		 * @return i32 
		 */
		i32 getDamageModifier();

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

        //Position of the player's command center.
        Vector3<f32> hallPosition;

        //Player's metal amount.
        i32 metalAmount;

        //Player's crystal amount.
        i32 crystalAmount;

        //Player's building range (for expandable terrains)
        f32 buildableRange;
        
    protected:
        //Happiness of the player's city.
        i32 happiness;

        //Player's city level.
        i32 cityLevel;

        //Player's army level.
        i32 armyLevel;

		//Player's max people amount.
		i32 maxPeople;

        //Player's citizens amount.
        i32 citizens;

		//Citizens generated by Happiness
		i32 citizensByHappiness;

        //Amount of damage avoided by a unit.
        i32 resistanceModifier;

        //Amount of modifyd damage of a unit.
        i32 damageModifier;

		//Count
		i32 influenceRangeIncrements;

        //True if player's city is under attack and false in other case.
        bool underAttack;
        
        //Time used to update the variables.
        Timer* resourceTimer;
        
        //Time used to update the variables.
        Timer* citizenTimer;
        
        //Player's buildings.
        BuildingManager *buildings;

        //PLayer's troops.
        UnitManager *units;

    private:
        
};

#endif