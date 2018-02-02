#ifndef BUILDING_H
#define BUILDING_H

#include "Entity.h"

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
         * @param id del edificio
         * @param parent es la capa padre
         * @param path ruta del archivo del modelo
         * @param buildingType es el tipo del edificio
         * @param vectorData es la posicion del edificio
         * @param teamData es el equipo al que pertenece
         */
        Building(int, SceneNode *, const wchar_t *, Enumeration::BuildingType, Vector3<float>, Enumeration::Team);
        /**
         * @brief Destructor
         */
        virtual ~Building();

        /**
         * @brief cobra al jugador del equipo correspondiente, 
         * el importe del edificio cuando se solicita su construccion
         * @param team indica el equipo al que pertenece el jugador
         */
        virtual void taxPlayer(Enumeration::Team);
        /**
         * @brief una vez vconstruido el edificio, actualiza la cantidad del mismo 
         * y los parametros de felicidad y numero de habitantes que tengan asociados
         * @param team indica el equipo al que pertenece el jugador
         */
        void specialTax(Enumeration::Team);
        /**
         * @brief solicita el color del edificio
         * @return devuelve el color de tipo irr::video::SColor
         */
        irr::video::SColor getColor();
        /**
         * @brief solicita el tipo de edificio
         * @return devuelve un entero con el tipo
         */
        int getType();
        /**
         * @brief actualiza el edificio
         */
        void update();
        /**
         * @brief Destructor
         * @return true si esta terminado y false en caso contrario 
         */
        bool getFinished();
        /**
         * @brief establece la hitbox del edificio
         */
        void setHitbox();
        /**
         * @brief Actualiza la hitbox del edificio
         */
        void updateHitbox();
        /**
         * @brief solicita el id del edificio
         * @return entero con el id 
         */
        int getID();
        
    private:
        /**
         * @brief Inicializa Building
         */
        void Init();

        int type;

        float updateHitboxTimer = 3;
        bool updated;

        //bool finished;
        float buildTimer;
        float buildCountdown;

        //irr::video::SColor baseColor;
        irr::video::SColor currentColor;
};

#endif