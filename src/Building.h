#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include <functional>
#include <EntityData.h>
#include <Types.h>
#include <IOEngine/Timer.h>

/**
 * @class Building.
 * @brief Create a Building type object. Public heritage from Entity class.
 */
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
        Building(SceneNode*, i32, Enumeration::Team, BuildingData);

        /**
         * @brief Building destructor.
         */
        virtual ~Building();

        /**
         * @brief Update the building while it is not finished.
         */
        void update();

        /**
         * @brief Start the building process
         */
        void startBuilding();
        
        /**
         * @brief Set the callback variable as the function passed by parameter.
         * 
         * @param std::function is the function to set as the callback variable of the building and have to be void and get a Building pointer as parameter.
         */
        void setFinishedCallback(std::function<void(Building*)>);

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
         * @brief Set the Can Build Mat object
         */
        void setCanBuildMat();

        /**
         * @brief Set the Cant Build Mat object
         */
        void setCantBuildMat();
        void takeDamage(i32 _damage);
        void setTarget(Entity *newTarget);
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

        //Building timer used for the construction time.
        Timer* buildTimer;

        //Finish the building.
        std::function<void(Building*)> callback;
        
        //
        Material *canBuildMat;
        
        //
        Material *cantBuildMat;
};

#endif