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
         * @param team
         * @param breed
		 */
        Entity(SceneNode *, int, const wchar_t *, Enumeration::Team, Enumeration::BreedType);
        /**
		 * @brief Destructor
		 */
        virtual ~Entity();

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
		 * @brief Actualiza el target de la entidad para ver si puede realizar un nuevo ataque
         * @param entity 
		 */
        void updateTarget(Entity*);
        /**
         * @brief Establece la hitbox de la entidad
         */
        void refreshHitbox();
        /**
		 * @brief Devuelve el color original al modelo
         * ToDo: cambiar por material
		 */
        void returnToOriginalColor();

        /**
		 * @brief Establece la posicion de la entidad
         * @param vertorData es las nuevas coordenadas de la posicion
		 */
        void setPosition(Vector3<float>);
        /**
         * @brief
         * @param
         */
        void setColor(irr::video::SColor);

        /**
		 * @brief Solicita el rango de ataque de la entidad
         * @return AttackRange de tipo entero
		 */
        int getAttackRange();
        /**
		 * @brief Devuelve el equipo al que pertenece la entidad
         * @return team tipo Enumeration::Team
		 */
        Enumeration::Team getTeam();
        /**
		 * @brief Devuelte la salud de la entidad
         * @return hp de tipo entero
		 */
        int getHP();
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
		 * @brief Devuelve el ViewRadius de la entidad
         * @return viewRadius de tipo entero
		 */
        int getViewRadius();
        /**
         * @brief solicita el id del edificio
         * @return entero con el id 
         */
        int getID();
        /**
         * @brief solicita el color del edificio
         * @return devuelve el color de tipo irr::video::SColor
         */
        irr::video::SColor getColor(); //ToDo: temporal
        
    protected:
        Model* model;
        Vector3<float> *position;
        Box3D<float>* hitbox;
        Enumeration::Team team;
        Enumeration::BreedType breed;

        int ID;

        float tookDamageTimer;
        float tookDamageCountdown;

        irr::video::SColor baseColor; //ToDo: cambiar por material

        Entity* target;
        
        // Values, costs, etc
        int currentHP;
        int maxHP;
        int viewRadius;
        int attackRange;
        int metalCost;
        int crystalCost;
        int happiness;
        int citizens;
        // For IA and info
        int cityLevel;
      private:
};

#endif