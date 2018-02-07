#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"
#include <functional>

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
         * @param parent es la capa padre
         * @param id del edificio
         * @param path ruta del archivo del modelo
         * @param teamData es el equipo al que pertenece
         * @param buildingType es el tipo del edificio
         * @param vectorData es la posicion del edificio
         */
        Building(SceneNode *, int, const wchar_t *, Enumeration::Team, Enumeration::BreedType, Enumeration::BuildingType, Vector3<float>);
        /**
         * @brief Destructor
         */
        virtual ~Building();

        /**
         * @brief cobra al jugador del equipo correspondiente, 
         * el importe del edificio cuando se solicita su construccion
         * @param team indica el equipo al que pertenece el jugador
         */
        void taxPlayer();
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
        void setFinishedCallback(std::function<void()>);
        
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
         * @brief Inicializa Building
         */
        void Init();

        //Building type
        Enumeration::BuildingType type;

        //Building timer
        float buildTimer;

        //Finish building callback
        std::function<void()> callback;

        //ToDo: cambiar color por material
        irr::video::SColor currentColor;
};

#endif