#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include <functional>
#include <EntityData.h>
#include <Types.h>
#include <IOEngine/Timer.h>

#include <irrlicht/irrlicht.h>
/**
 * @class Building.
 * @brief Create a Building type object. Public heritage from Entity class.
 */
class BuildingManager;
class Building : public Entity {
    public:
        /**
         * @brief Buiding constructor.
         * 
         * @param SceneNode is the layer where the building will be created.
         * @param id32 is the id number that will identify the building.
         * @param Enumeration::Team is the team to which belongs the building: Enumeration::Team::Human or Enumeration::Team::IA.
         * @param BuildingData is the data of the building.
         */
        Building(SceneNode*, i32, Enumeration::Team, BuildingData, BuildingManager* _buildingManager);

        /**
         * @brief Building destructor.
         */
        virtual ~Building();
		
        /**
         * @brief Start the building process
         */
        void startBuilding();

		/**
		 * @brief 
		 * 
		 * @param _damage 
		 */
        void takeDamage(i32 _damage);

        /**
         * @brief Set the callback variable as the function passed by parameter.
         * 
         * @param std::function is the function to set as the callback variable of the building and have to be void and get a Building pointer as parameter.
         */
        void setFinishedCallback(std::function<void(Building*)>);

        /**
         * @brief Set the Cant Build Mat object
         */
        void setCantBuildColor();

		/**
		 * @brief Set the Building Color object
		 * 
		 */
		void setBuildingColor();

		/**
		 * @brief Set the Target object
		 * 
		 * @param newTarget 
		 */
        void setTarget(Entity *newTarget);

        /**
         * @brief Get the finished variable of the building.
         * 
         * @return Value finished variable (true if the building is finished or false if it is not).
         */
        bool getFinished();

        /**
         * @brief Get the type variable of the building.
         * 
         * @return std::string that will be the value of the type variable.
         */
        std::string getType();

		/**
		 * @brief Get the Building Time object
		 * 
		 * @return i32 
		 */
		i32 getBuildingTime();
    private:
        /**
         * @brief Subtract the metal and crystal cost of the building to the metal and crystal available of the player (Human or IA) and add the city level that provided by the building to the player's city level (Human or IA).
         */
        void taxPlayer();

        /**
         * @brief Add the happiness and citizens provided by the building to the player's happiness and citizens (Human or IA).
         */
        void adjustCityStats();

        //Amount of level that provides to the player's city.
        i32 cityLevel;

        //Type of the building
        std::string buildingType;

		//
		i32 buildingTime;

        //Building timer used for the construction time.
        Timer* buildTimer;

        //Finish the building.
        std::function<void(Building*)> callback;

		//
        BuildingManager* buildingManager;
};

#endif