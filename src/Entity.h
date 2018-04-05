#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <Types.h>
#include <Enumeration.h>
#include <MathEngine/Vector3.h>
#include <MathEngine/Box3D.h>
#include <MathEngine/Box2D.h>
#include <GraphicEngine/Model.h>
#include <GraphicEngine/SceneNode.h>

/**
 * @class Entity.
 * @brief Create a Entity type object.
 */
class Entity {

    public:
        /**
         * @brief Entity constructor.
         * @param The id32 is the id number that will identify the entity.
         * @param The Enumeration::Team is the team to which belongs the entity: Enumeration::Team::Human or Enumeration::Team::IA.
         * @param The Enumeration::BreedType is the civilization to which belongs the entity: Enumeration::BreedType::Drorania or Enumeration::BreedType::Kaonov.
         */
        Entity(i32, Enumeration::Team, Enumeration::BreedType);

        /**
		 * @brief Entity destructor
		 */
        virtual ~Entity();

        /**
         * @brief Subtract damage passed by parameter to currentHP variable.
         * @param The i32 is the damage that is going to be subtracted to currentHP variable.
		 */
        void takeDamage(i32);

        /**
		 * @brief Set target as the value passed by parameter
         * @param The pointer to Entity is the value that is going be assigned to target variable. It can be NULL.
		 */
        void setTarget(Entity*);

        /**
         * @brief Set the entity hitbox.
         */
        void refreshHitbox();

        /**
		 * @brief Set the color of the model to its original color unless tookDamageCountdown variable is higher than 0.
         * @see setColor(irr::video::SColor) method of Entity class.
         * ToDo: cambiar por material
		 */
        void returnToOriginalColor();

        /**
         * @brief Create the model, hitbox and position of the entity.
         * @param The SceneNode is a pointer to the layer where is going to be created the entity.
         * @param The const wchar_t is a pointer to the path of the file with the model.
         */
        void setModel(SceneNode *, const wchar_t *);
        
        /**
		 * @brief Set the position of the model, hitbox, hitBox and position variables as the one passed by parameter.
         * @param The Vector3 is the value that is going to be assigned as position to model, hitbox, hitBox and position variables.
		 */
        void setPosition(Vector3<f32>);

        /**
         * @brief Set currentColor variable as the one passed by parameter.
         * @param The irr::video::SColor is the color that is going to be assigned to currentColor variable.
         */
        void setColor(irr::video::SColor);

        /**
         * @brief Set a new id to the entity.
         * @param The i32 is the value that is going to be assigned to ID variable.
         */
        void setID(i32);

        /**
         * @brief Get current traget of the entity.
         * @return A pointer to an Entity object if the entity has current target and NULL in other case.
         */
        Entity* getTarget();

        /**
		 * @brief Get the attack range of the entity.
         * @return i32 that will be the value of attackRange variable.
		 */
        i32 getAttackRange();

        /**
		 * @brief Get the team of the entity.
         * @return Enumeration::Team that will be the value of team variable: Enumeration::Team::Human or Enumeration::Team::IA.
		 */
        Enumeration::Team getTeam();
        
        /**
         * @brief Get the type of the entity.
         * @return Enumeration::EntityType that will be the value of entityType variable: Enumeration::EntityType::Building or Enumeration::EntityType::Unit.
         */
        Enumeration::EntityType getEntityType();

        /**
		 * @brief Get the current hp of the entity.
         * @return i32 that will be the current value of currentHP variable.
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

         /**
          * @brief
          * @return
          */
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

        /**
         * @breif
         * @return
         */
        i32 getCellsX();

        /**
         * @breif
         * @return
         */
        i32 getCellsY();

        /**
         * @breif
         * @return
         */
        Box2D getHit();

        /**
         * @breif
         * @return
         */
        i32 getArmyLevel();

        /**
         * @breif
         * @return
         */
        std::vector<Entity*> getHostile();

        /**
         * @breif
         * @param
         */
        void addHostile(Entity*);

        /**
         * @breif
         * @param
         */
        void removeHostile(Entity*);

        /**
         * @breif
         * @param
         */
        void putHostileTargetsToNull();

    protected:
        Model* model;
        Vector3<f32> *position;
        Box3D<f32>* hitbox;
        Box2D hitBox;
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

        std::vector<Entity*> hostile;

        i32 kCellsX;
        i32 kCellsY;
      private:
};

#endif