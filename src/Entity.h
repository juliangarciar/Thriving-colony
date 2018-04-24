#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <Types.h>
#include <Enumeration.h>
#include <MathEngine/Box2D.h>
#include <GraphicEngine/Model.h>
#include <GraphicEngine/SceneNode.h>
#include <GraphicEngine/Material.h>
#include <GraphicEngine/Billboard.h>
#include <IOEngine/Timer.h>

/**
 * @class Entity.
 * @brief Create a Entity type object.
 */
class Entity {
    public:
        /**
         * @brief Construct a new Entity object
         * 
         * @param _layer is the Layer of the entity
         * @param _id is the id number that will identify the entity.
         * @param _team is the team to which belongs the entity: Enumeration::Team::Human or Enumeration::Team::IA.
         * @param _type is type of entity.
         * @param _maxHP 
         * @param _maxView 
         * @param _attackRange 
         * @param _attackDamage 
         * @param _attackSpeed 
         * @param _metal 
         * @param _crystal 
         * @param _happines 
         * @param _citizens 
         * @param _cellsX 
         * @param _cellsY 
         * @param _modelPath 
         * @param _texturePath 
         */
        Entity(
            SceneNode* _layer,
            i32 _id,
            Enumeration::Team _team,
            Enumeration::EntityType _type,
            i32 _maxHP,
            i32 _maxView,
            i32 _attackRange,
            i32 _attackDamage,
            i32 _attackSpeed,
            i32 _metal,
            i32 _crystal,
            i32 _happines,
            i32 _citizens,
            i32 _cellsX,
            i32 _cellsY,
            std::string _modelPath,
            std::string _texturePath
        );

        /**
         * @brief Entity destructor
         */
        virtual ~Entity();

        /**
         * @brief Update the entity
         * 
         */
        void update();

        /**
         * @brief Subtract damage passed by parameter to currentHP variable.
         * @param i32 is the damage that is going to be subtracted to currentHP variable.
	    */
        void takeDamage(i32);

        /**
         * @breif Add an entity to the vector of enemies that have as target the entity.
         * @param Pointer to the entity that is going to be added to hostile variable.
         */
        void addHostile(Entity* hostileTarget);

        /**
         * @breif Remove an entity from the vector of enemies that have as target the entity.
         * @param Pointer to de the entity that is going to be removed from hostile variable.
         */
        void removeHostile(Entity* hostileTarget);

        /**
         * @breif Set all the enemies' target variable stored at hostile variable to nullptr.
         */
        void putHostileTargetsToNull();

        /**
         * @brief Set a new id to the entity.
         * @param i32 is the value that is going to be assigned to ID variable.
         */
        void setID(i32 idValue);
        
        /**
         * @brief Set the position of the model, hitbox, hitBox and position variables as the one passed by parameter.
         * @param Vector3 is the value that is going to be assigned as position to model, hitbox, hitBox and position variables.
	     */
        void setPosition(Vector2<f32> positionVector);

        /**
	     * @brief Set target as the value passed by parameter
         * @param pointer to Entity is the value that is going be assigned to target variable. It can be nullptr.
	     */
        void setTarget(Entity*);

        /**
         * @brief Get the Layer object
         * 
         * @return SceneNode* 
         */
        SceneNode *getLayer();

        /**
         * @brief Get id of the entity.
         * @return i32 that will be the value of the ID variable.
         */
        i32 getID() const;

        /**
	     * @brief Get the team of the entity.
         * @return Enumeration::Team that will be the value of team variable: Enumeration::Team::Human or Enumeration::Team::IA.
	     */
        Enumeration::Team getTeam() const; 
        
        /**
         * @brief Get the type of the entity.
         * @return Enumeration::EntityType that will be the value of entityType variable: Enumeration::EntityType::Building or Enumeration::EntityType::Unit.
         */
        Enumeration::EntityType getEntityType() const;

        /**
	     * @brief Get the model of the entity.
         * @return Pointer to a Model object that will be the value of the model variable.
	     */
        Model* getModel() const;

        /**
	     * @brief Get the current position of the entity.
         * @return Pointer to a Vector3 objetc that will be the value of the position variable.
	     */
        Vector2<f32> getPosition() const; 

        /**
         * @brief gets the hitbox
         * @return
         */
        Box2D getHitbox() const;

        /**
	     * @brief Get the current hp of the entity.
         * @return i32 that will be the current value of currentHP variable.
	     */
        i32 getCurrentHP() const;

        /**
	     * @brief Get the max hp of the entity.
         * @return i32 that will be the value of maxHP variable.
	     */
        i32 getMaxHP() const;

        /**
	     * @brief Get the distance until where the entity can see enemies.
         * @return i32 that will be the value of the viewRadius variable.
	     */
        i32 getViewRadius() const;

        /**
	     * @brief Get the attack range of the entity.
         * @return i32 that will be the value of attackRange variable.
	     */
        i32 getAttackRange() const;

        /**
	     * @brief Get the attack damage of the entity.
         * @return i32 that will be the value of attackDamage variable.
	     */
        i32 getAttackDamage() const;

        /**
	     * @brief Get the attack speed of the entity.
         * @return i32 that will be the value of attackSpeed variable.
	     */
        i32 getAttackSpeed() const;

        /**
         * @brief Get the Metal Cost
         * @return i32 
         */
        i32 getMetalCost() const;

        /**
         * @brief Get the Crystal Cost
         * @return i32 
         */
        i32 getCrystalCost() const;

         /**
          * @brief Get the happiness that the entity provides to the player's city.
          * @return i32 that will be the value of the happiness variable.
          */
        i32 getHappinessVariation() const;

        /**
         * @brief Get the Citizens Variation
         * @return i32 
         */
        i32 getCitizensVariation() const;

        /**
         * @brief Get current traget of the entity.
         * @return A pointer to an Entity object if the entity has current target and nullptr in other case.
         */
        Entity* getTarget() const;

        /**
         * @breif Get all the enemies that have as target the entity.
         * @return std::vector<Entity*> that will be the value of the hostile variable.
         */
        std::vector<Entity*> getHostile() const;

        /**
         * @brief
         * @return
         */
        i32 getCellsX() const;

        /**
         * @brief
         * @return
         */
        i32 getCellsY() const;

		//ToDo: anadido por rafa
        /**
         * @brief Set the Base Material object
         */
        void setBaseMaterial();

        /**
         * @brief Set the Damaged Material object
         */
        void setDamagedMaterial();
    protected:
        //Layer for the model
        SceneNode* layer;

        //Number that identifies the entity.
        i32 ID;

        //Team to which belongs the entity: Enumeration::Team::Human or Enumeration::Team::IA.
        Enumeration::Team team;

        //Type of the entity: Enumeration::EntityType::Unit or Enumeration::EntityType::Building.
        Enumeration::EntityType entityType;

        //Pointer to the model of the entity.
        Model* model;

        //Pointer to the position of the entity.
        Vector2<f32> vectorPos;

        //HitBox
        Box2D hitBox;
        
        //Current hp of the entity.
        i32 currentHP;

        //Maximun hp of the entity.
        i32 maxHP;

        //Distance until where the entity can see enemies.
        i32 viewRadius;

        //Distance until where the entity can attack enemies.
        i32 attackRange;

        //Distance until where the entity can attack enemies.
        i32 attackDamage;

        //Distance until where the entity can attack enemies.
        i32 attackSpeed;

        //Metal cost of the entity.
        i32 metalCost;

        //Crystal cost of the entity.
        i32 crystalCost;

        //Happines that the entity provides to the player's city.
        i32 happinessVariation;

        //Cityzens that give/take
        i32 citizensVariation;

        //Pointer to the enemy that is going to be attacked by the entity. Can be nullptr.
        Entity* target;

        //Hostile units vector
        std::vector<Entity*> hostile;

        //Took damage timer
        Timer *tookDamageTimer;

        //CellSpace info
        i32 kCellsX;
        i32 kCellsY;
        //
        Material *baseMat;

        //
        Material *damagedMat;
        Billboard* barBg;
        Billboard* bar;
};
#endif