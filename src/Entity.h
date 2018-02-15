#ifndef ENTITY_H
#define ENTITY_H

#include <GraphicEngine/Vector3.h>
#include <GraphicEngine/Box3D.h>
#include <GraphicEngine/Model.h>
#include <GraphicEngine/SceneNode.h>
#include "Enumeration.h"
//#include "Battle.h"
#include <Types.h>

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
         * @param team
         * @param breed
		 */
        Entity(i32, Enumeration::Team, Enumeration::BreedType);
        /**
		 * @brief Destructor
		 */
        virtual ~Entity();

        /**
        * @brief Resta el daño que se le haga a una unidad a tu salud total
         * @param dmg es el daño a restar
		 */
        void takeDamage(i32);
        /**
		 * @brief Mueve el objeto 3D a las coordenadas (0,0,0)
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
         * @brief 
         * 
         * @param path 
         */
        void setModel(SceneNode *, const wchar_t *);
        
        /**
		 * @brief Establece la posicion de la entidad
         * @param vertorData es las nuevas coordenadas de la posicion
		 */
        void setPosition(Vector3<f32>);
        /**
         * @brief
         * @param
         */
        void setColor(irr::video::SColor);
        /**
         * @brief set the id
         * @param id
         */
        void setID(i32);

        /**
		 * @brief Solicita el rango de ataque de la entidad
         * @return AttackRange de tipo entero
		 */
        i32 getAttackRange();
        /**
		 * @brief Devuelve el equipo al que pertenece la entidad
         * @return team tipo Enumeration::Team
		 */
        Enumeration::Team getTeam();
        
        Enumeration::EntityType getEntityType();
        /**
		 * @brief Devuelte la salud de la entidad
         * @return hp de tipo entero
		 */
        i32 getHP();
        /**
		 * @brief Solicita la posicion actual de la entidad
         * @return position sera el vector de coordenadas devuelto
		 */
        Vector3<f32> *getPosition();
        /**
		 * @brief Solicita la hitbox de la entidad
         * @return hitbox de tipo Box3D
		 */
        Box3D<f32> *getHitbox();
        /**
		 * @brief Solicita el modelo 3D de la entidad
         * @return model3D de tipo Model
		 */
        Model *getModel();
        /**
		 * @brief Devuelve el ViewRadius de la entidad
         * @return viewRadius de tipo entero
		 */
        i32 getViewRadius();
        /**
         * @brief solicita el id del edificio
         * @return entero con el id 
         */
        i32 getID();

        i32 getHappiness();
        
        /**
         * @brief solicita el color del edificio
         * @return devuelve el color de tipo irr::video::SColor
         */
        irr::video::SColor getBaseColor(); //ToDo: cambiar por material
        /**
         * @brief solicita el color del edificio
         * @return devuelve el color de tipo irr::video::SColor
         */
        irr::video::SColor getCurrentColor(); //ToDo: cambiar por material
        // Added by Julian
        i32 getCells();

        i32 getArmyLevel();

    protected:
        Model* model;
        Vector3<f32> *position;
        Box3D<f32>* hitbox;
        Enumeration::Team team;
        Enumeration::BreedType breed;
        Enumeration::EntityType entityType;

        i32 ID;

        f32 tookDamageTimer;
        f32 tookDamageCountdown;

        irr::video::SColor baseColor; //ToDo: cambiar por material
        irr::video::SColor currentColor; //ToDo: cambiar color por material

        Entity* target;
        
        // Values, costs, etc
        i32 currentHP;
        i32 maxHP;
        i32 viewRadius;
        i32 attackRange;
        i32 metalCost;
        i32 crystalCost;
        i32 happiness;
        i32 citizens;
        // For IA and info
        i32 cityLevel;
        i32 armyLevel;

        // Added by Julian
        i32 kCells;
      private:
};

#endif