#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include <functional>
#include <Types.h>

/**
 * @class Building.
 * @brief Create a Building type object. Public heritage from Entity class.
 */
class Building : public Entity {
    
    public:
        /**
         * @brief Buiding constructor.
         * @param The SceneNode is the layer where the building will be created.
         * @param The id32 is the id number that will identify the building.
         * @param The Enumeration::Team is the team to which belongs the building: Enumeration::Team::Human or Enumeration::Team::IA.
         * @param The Enumeration::BreedType is the civilization to which belongs the building: Enumeration::BreedType::Drorania or Enumeration::BreedType::Kaonov.
         * @param The Enumeration::BuildingType is the building type.
         */
        Building(SceneNode *, i32, Enumeration::Team, Enumeration::BreedType, Enumeration::BuildingType);

        /**
         * @brief Building destructor.
         */
        virtual ~Building();

        /**
         * @brief Subtract the metal and crystal cost of the building to the metal and crystal available of the player (Human or IA) and
         * add the city level that provided by the building to the player's city level (Human or IA).
         */
        void preTaxPlayer();

        /**
         * @brief Add the happiness and citizens provided by the building to the player's happiness and citizens (Human or IA).
         */
        void posTaxPlayer();

        /**
         * @brief Update the building while it is not finished.
         */
        void update();

        /**
         * @brief Finish the building.
         */
        void triggerFinishedCallback();

        /**
         * @brief Set the callback variable as the function passed by parameter.
         * @param The std::function is the function to set as the callback variable of the building and have to be void and get a Building pointer as parameter.
         */
        void setFinishedCallback(std::function<void(Building*)>);
        
        /**
         * @brief Get the type variable of the building.
         * @return Value of the type variable.
         */
        Enumeration::BuildingType getType();

        /**
         * @brief Get the finished variable of the building.
         * @return Value finished variable (true if the building is finished or false if it is not).
         */
        bool getFinished();
        
    private:
        /**
         * @brief Initialize the building.
         */
        void Init();

        //Layer where the building was created.
        SceneNode *layer;

        //Building type
        Enumeration::BuildingType type;

        //Building timer used for the construction time.
        f32 buildTimer;

        //Finish building callback
        std::function<void(Building*)> callback;

        //True if the building is finished and false if it is not.
        bool finished;

        //True if the building is near the camera and false if not. It is used to do the level of detail of the mesh
        bool near;
};

#endif