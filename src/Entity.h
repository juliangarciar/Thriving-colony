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
#include <IOEngine/Timer.h>
#include <GraphicEngine/Material.h>

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
		 * @brief Get the current position of the entity.
         * @return Pointer to a Vector3 objetc that will be the value of the position variable.
		 */
        Vector3<f32> *getPosition();

        /**
		 * @brief Get the hitbox of the entity.
         * @return Pointer to a Box3D object that will be the value of the hitbox variable.
		 */
        Box3D<f32> *getHitbox();

        /**
		 * @brief Get the model of the entity.
         * @return Pointer to a Model object that will be the value of the model variable.
		 */
        Model *getModel();

        /**
		 * @brief Get the distance until where the entity can see enemies.
         * @return i32 that will be the value of the viewRadius variable.
		 */
        i32 getViewRadius();

        /**
         * @brief Get id of the entity.
         * @return i32 that will be the value of the ID variable.
         */
        i32 getID();

         /**
          * @brief Get the happiness that the entity provides to the player's city.
          * @return i32 that will be the value of the happiness variable.
          */
        i32 getHappiness();
        
        /**
         * @brief Get the color of the entity.
         * @return irr::video::SColor that will be the value of the baseColor variable.
         */
        irr::video::SColor getBaseColor(); //ToDo: cambiar por material

        /**
         * @brief Get the current color of the entity.
         * @return irr::video::SColor that will be the value of the currentColor variable.
         */
        irr::video::SColor getCurrentColor(); //ToDo: cambiar por material

        /**
         * @brief
         * @return
         */
        i32 getCellsX();

        /**
         * @brief
         * @return
         */
        i32 getCellsY();

        /**
         * @brief
         * @return
         */
        Box2D getHit();

        /**
         * @brief Get the army level that the entity provides to the player's city.
         * @return i32 that will be the value of the armyLevel variable.
         */
        i32 getArmyLevel();

        /**
         * @brief Get all the enemies that have as target the entity.
         * @return std::vector<Entity*> that will be the value of the hostile variable.
         */
        std::vector<Entity*> getHostile();

        /**
         * @brief Add an entity to the vector of enemies that have as target the entity.
         * @param Pointer to the entity that is going to be added to hostile variable.
         */
        void addHostile(Entity*);

        /**
         * @brief Remove an entity from the vector of enemies that have as target the entity.
         * @param Pointer to de the entity that is going to be removed from hostile variable.
         */
        void removeHostile(Entity*);

        /**
         * @brief Set all the enemies' target variable stored at hostile variable to NULL.
         */
        void putHostileTargetsToNull();

        void setBaseMaterial();

        void setDamagedMaterial();

    protected:
        //Pointer to the model of the entity.
        Model* model;

        //Pointer to the position of the entity.
        Vector3<f32> *position;

        //Pointer to the hitbox of the entity.
        Box3D<f32>* hitbox;

        //
        Box2D hitBox;

        //Team to which belongs the entity: Enumeration::Team::Human or Enumeration::Team::IA.
        Enumeration::Team team;

        //Civilization to which belongs the entity: Enumeration::BreedType::Drorania or Enumeration::BreedType::Kaonov.
        Enumeration::BreedType breed;

        //Type of the entity: Enumeration::EntityType::Unit or Enumeration::EntityType::Building.
        Enumeration::EntityType entityType;

        //Number that identifies the entity.
        i32 ID;

        Timer* tookDamageTimer;

        //Base color of the entity.
        irr::video::SColor baseColor; //ToDo: cambiar por material
        Material *baseMat;
        Material *damagedMat;


        //Current color of the entity.
        irr::video::SColor currentColor; //ToDo: cambiar color por material

        //Pointer to the enemy that is going to be attacked by the entity. Can be NULL.
        Entity* target;
        
        //Current hp of the entity.
        i32 currentHP;

        //Maximun hp of the entity.
        i32 maxHP;

        //Distance until where the entity can see enemies.
        i32 viewRadius;

        //Distance until where the entity can attack enemies.
        i32 attackRange;

        //Metal cost of the entity.
        i32 metalCost;

        //Crystal cost of the entity.
        i32 crystalCost;

        //Happines that the entity provides to the player's city.
        i32 happiness;

        //Citiziens that the entity provides to the player's city.
        i32 citizens;
        
        //Level that the entity provides to the player's city.
        i32 cityLevel;

        //Army level that the entity provides to the palyer's city.
        i32 armyLevel;

        //All enemies that have as target the entity.
        std::vector<Entity*> hostile;

        //
        i32 kCellsX;

        //
        i32 kCellsY;
        
      private:
};

#endif