#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <Types.h>
/* Maybe enumeraiton should be removed */
#include <Enumeration.h>
//#include <MathEngine/Vector3.h>
#include <MathEngine/Box3D.h>
#include <MathEngine/Box2D.h>


class Model;
class SceneNode;
/**
 * @class Entity
 * @brief Crea un objeto tipo Entity
 */
class Entity {

    public:
        Entity(i32, Enumeration::Team, Enumeration::BreedType);
        virtual ~Entity();
        /* MAIN FUNCTIONS */
        void updateTarget(Entity*);
        void returnToOriginalColor();
        void refreshHitbox();
        /* SETTERS */
        void takeDamage(i32);
        void setModel(SceneNode* sNode, const wchar_t* modelPath);
        void setPosition(Vector2<f32> positionVector);
        void setColor(irr::video::SColor);
        void setID(i32 idValue);
        void setTarget(Entity* target);
        void addHostile(Entity* hostileTarget);
        void removeHostile(Entity* hostileTarget);
        void putHostileTargetsToNull();
        
        /* GETTERS */
        i32 getHP() const;
        i32 getViewRadius() const;
        /* Same as above, we already got enums */
        i32 getHappiness() const;
        i32 getID() const;
        /* Is this needed? We just need to know that's an entity (?) */
        Enumeration::Team getTeam() const;
        Enumeration::EntityType getEntityType() const;
        Model* getModel() const;
        irr::video::SColor getBaseColor() const;
        irr::video::SColor getCurrentColor() const; //ToDo: cambiar por material
        std::vector<Entity*> getHostile() const;
        Entity* getTarget() const;
        Vector2<f32> getPosition() const; 
        Box3D<f32> getHitBox() const;
        Box2D getHit() const;
        //std::vector<i32> getCellSpace() const;
        /* Check to delete */
        i32 getAttackRange() const;
        i32 getArmyLevel() const;
        i32 getCellsX() const;
        i32 getCellsY() const;
    protected:
        i32 maxHP;
        i32 currentHP;
        /* This should be const */
        i32 viewRadius;
        /* Check to delete */
        i32 attackRange;
        /* Why we need this?, we already got enums for this purpose */
        i32 metalCost;
        i32 crystalCost;
        i32 happiness;

        i32 ID;
        Enumeration::Team team;
        Enumeration::BreedType breed;
        Enumeration::EntityType entityType;

        Model* model;
        irr::video::SColor baseColor; //ToDo: cambiar por material
        irr::video::SColor currentColor; //ToDo: cambiar color por material
        /* Check to delete */
        Box3D<f32> hitbox;
        Box2D hitBox;
        /* More const */
        f32 tookDamageTimer;
        f32 tookDamageCountdown;        

        std::vector<Entity*> hostile;
        Entity* target;

        Vector2<f32> vectorPos;
        
        std::vector<i32> kCells;
        // Values, costs, etc

        /* Move to Unit */
        i32 citizens;
        // For IA and info
        /* Move to building */
        i32 cityLevel;
        /* Move to Unit */
        i32 armyLevel;
        /* Why? */
        
        /* Check to delete */
        i32 kCellsX;
        i32 kCellsY;
};

#endif