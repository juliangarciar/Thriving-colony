#ifndef ENTITY_H
#define ENTITY_H

#include <GraphicEngine/Vector3.h>
#include <GraphicEngine/Box3D.h>
#include <GraphicEngine/Model.h>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Window.h>
#include "Enumeration.h"
//#include "Battle.h"

/**
 * @class Entity
 * @brief Crea un objeto tipo Entity
 */
class Entity {

    public:
        /**
		 * @brief Constructor
         * @param layer sera la capa en la que se encuentra la entidad
         * @param id de la entidad
         * @param path con la ruta del archivo del modelo 3D
		 */
        Entity(SceneNode *, int, const wchar_t *);
        /**
		 * @brief Destructor
		 */
        virtual ~Entity();

        /**
		 * @brief Devuelte la salud de la entidad
         * @return hp de tipo entero
		 */
        int getHP();
        
        int getID();
        void setID(int);
        /**
		 * @brief Resta el daño que se le haga a una unidad a tu salud total
         * @param dmg es el daño a restar
		 */
        void takeDamage(int);
        /**
		 * @brief Mueve el objeto 3D a las coordenadas (0,0,0)
		 */
        void die();

        /**
		 * @brief Establece la posicion de la entidad
         * @param vertorData es las nuevas coordenadas de la posicion
		 */
        void setPosition(Vector3<float>);

        /**
		 * @brief Devuelve el equipo al que pertenece la entidad
         * @return team tipo Enumeration::Team
		 */
        Enumeration::Team getTeam();
        
        Enumeration::EntityType getEntityType();
        /**
		 * @brief Solicita la posicion actual de la entidad
         * @return position sera el vector de coordenadas devuelto
		 */
        Vector3<float> *getPosition();
        /**
		 * @brief Solicita la hitbox de la entidad
         * @return hitbox de tipo Box3D
		 */
        Box3D<float> *getHitbox();
        /**
		 * @brief Solicita el modelo 3D de la entidad
         * @return model3D de tipo Model
		 */
        Model *getModel();
        /**
		 * @brief Actualiza el target de la entidad para ver si puede realizar un nuevo ataque
         * @param entity 
		 */
        void updateTarget(Entity*);

        /**
		 * @brief Solicita el rango de ataque de la entidad
         * @return AttackRange de tipo entero
		 */
        int getAttackRange();
        /**
		 * @brief Cambia el color del modelo a rojo cuando la entidad esta siendo atacada
		 */
        void changeRedTint();

        /**
         * @brief cobra al jugador del equipo correspondiente, 
         * el importe del edificio cuando se solicita su construccion
         * @param team indica el equipo al que pertenece el jugador
         */
        virtual void taxPlayer(Enumeration::Team) = 0;
        /**
		 * @brief Devuelve el ViewRadius de la entidad
         * @return viewRadius de tipo entero
		 */
        int getViewRadius();
        
    protected:
        Entity* target;
        
        Model* model;
        Vector3<float> *position;
        Box3D<float>* hitbox;

        int ID;

        int hpMax;
        int hp;
        int viewRadius;

        irr::video::SColor baseColor;

        // Values, costs, etc
        int happiness;
        int cityLevel;
        int metalCost;
        int crystalCost;

        int attackRange;
        
        Enumeration::Team team;
        Enumeration::EntityType entityType;

        float tookDamageTimer;
        float tookDamageCountdown;

        bool finished;

      private:
};

#endif