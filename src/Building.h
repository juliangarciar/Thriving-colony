#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include <functional>
#include <Types.h>
#include <IOEngine/Timer.h>

struct BuildingData {
    std::string type;
    f32 buildTime;
    i32 metalCost;
    i32 crystalCost;
};

/**
 * @class Building.
 * @brief Create a Building type object. Public heritage from Entity class.
 */
class Building : public Entity {
    
    public:
        /**
         * @brief Buiding constructor.
         * @param SceneNode is the layer where the building will be created.
         * @param id32 is the id number that will identify the building.
         * @param Enumeration::Team is the team to which belongs the building: Enumeration::Team::Human or Enumeration::Team::IA.
         * @param BuildingData is the data of the building
         */
        Building(SceneNode *, i32, Enumeration::Team, BuildingData);

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
         * @param std::function is the function to set as the callback variable of the building and have to be void and get a Building pointer as parameter.
         */
        void setFinishedCallback(std::function<void(Building*)>);

        /**
         * @brief Get the finished variable of the building.
         * @return Value finished variable (true if the building is finished or false if it is not).
         */
        bool getFinished();

        /**
         * @brief Get the Type
         * @return std::string 
         */
        std::string getType();
        
    private:
        /**
         * @brief Subtract the metal and crystal cost of the building to the metal and crystal available of the player (Human or IA) and
         * add the city level that provided by the building to the player's city level (Human or IA).
         */
        void taxPlayer();

        /**
         * @brief Add the happiness and citizens provided by the building to the player's happiness and citizens (Human or IA).
         */
        void adjustCityStats();

        //Layer where the building was created.
        SceneNode *layer;

        //Building type
        BuildingData data;

        //Building timer used for the construction time.
        Timer* buildTimer;

        //Finish building callback
        std::function<void(Building*)> callback;

        //True if the building is finished and false if it is not.
        bool finished;

        //True if the building is near the camera and false if not. It is used to do the level of detail of the mesh
        bool near;

        //ToDo: explicar aqui para que sirve esto
        i32 cityLevel;
};

#endif