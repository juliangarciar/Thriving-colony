#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include <functional>
#include <Types.h>

/**
 * @class Building
 * @brief Crea un objeto tipo Building
 */
class Building : public Entity {
    
    public:
        //Enum: Barn,Barrack,Hospital,House,MainBuilding,Market,Quarry,Siderurgy,School,Tower,Wall,Workshop
        //teamData sepecifies the building team and vectorData the position

        /**
         * @brief Constructor de Buiding
         * @param layer
         * @param id del edificio
         * @param teamData es el equipo al que pertenece
         * @param BreedType es el equipo al que pertenece
         * @param buildingType es el tipo del edificio
         */
        Building(SceneNode *, i32, Enumeration::Team, Enumeration::BreedType, Enumeration::BuildingType);
        /**
         * @brief Destructor
         */
        virtual ~Building();

        /**
         * @brief cobra al jugador del equipo correspondiente, 
         * el importe del edificio cuando se solicita su construccion
         */
        void preTaxPlayer();
        /**
         * @brief cobra al jugador del equipo correspondiente, 
         * el importe del edificio cuando se termina de construir
         */
        void posTaxPlayer();
        /**
         * @brief actualiza el edificio
         */
        void update();
        /**
         * @brief finaliza el edificio
         */
        void triggerFinishedCallback();

        /**
         * @brief
         * @param
         */
        void setFinishedCallback(std::function<void(Building*)>);
        
        /**
         * @brief solicita el tipo de edificio
         * @return devuelve un entero con el tipo
         */
        Enumeration::BuildingType getType();
        /**
         * @brief Destructor
         * @return true si esta terminado y false en caso contrario 
         */
        bool getFinished();
        
    private:
         /**
         * @brief Called from the destructor, clears the cells
         */
        void Clear();
        /**
         * @brief Inicializa Building
         */
        void Init();

        //Scene Node
        SceneNode *layer;

        //Building type
        Enumeration::BuildingType type;

        //Building timer
        f32 buildTimer;

        //Finish building callback
        std::function<void(Building*)> callback;

        //is built
        i32 finished;
};

#endif