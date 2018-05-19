#ifndef UNIT_H
#define UNIT_H


#include <string>
#include <list>
#include <Types.h>
#include <Entity.h>
#include <PathPlanner/PathManager.h>
#include <EntityData.h>
#include <Enumeration.h>

class UnitManager;
class Sensor;
class UnitFighter;
/**
 * @class Unit.
 * @brief Create a Unit type object. Public heritage from Entity class.
 */
class Unit : public Entity {
    
    public:
        Unit(SceneNode* _layer, i32 _id, Enumeration::Team _team, UnitData baseData, UnitManager* _unitManager);
        /* Initialize functions */
        virtual ~Unit();
        virtual void preTaxPlayer();
        /* Do something functions */
        void Init();
        void update();
        void switchState(Enumeration::UnitState);
        void recruitingState();
        void inHomeState();
        void idleState();
        void moveState();
        void attackMoveState();
        void attackState();
        void chaseState();
        void retractState();
        void moveUnit();
        void triggerRecruitedCallback();
        void triggerRetractedCallback();
        void setUnitCell(Vector2<f32>);
        void setUnitPosition(Vector2<f32>);
        void setUnitDestination(Vector2<f32>);
        void setPath(const std::list< Vector2<f32> >&);
        void setPathToTarget(Vector2<f32>);
        void setRecruitedCallback(std::function<void(Unit*)>);
        void setRetractedCallback(std::function<void(Unit*)>);
        void takeDamage(i32 _damage);
        void setTarget(Entity *newTarget);
        /* Getters */
        bool inRangeOfAttack();
        const std::string getAttackEvent() const;
        const std::string getMoveEvent() const;
        const std::string getSelectEvent() const;
        Vector2<f32> getDestination() const;
        const std::list< Vector2<f32> >& getPath() const;
        const std::string getType() const;
        Enumeration::UnitState getState() const;
        const i32 getArmyLevel() const;
        const std::vector< Vector2<f32> >& getUnitFightersPosition() const; /* Not implemented */    
        const std::vector< UnitFighter* >& getUnitFighters() const;

    private:
        bool hasArrived();
        void calculateDirection();
        void updateUnitFighters();
        void updateFlockingSensor();

        Enumeration::UnitState state;
        const std::string type;
        const i32 moveSpeed;
        const i32 attackSpeed;
        const i32 attackDamage;
        bool moving;
        bool canAttack;
        const i32 armyLevel;

        Timer* recruitingTimer;
        Timer* enemySensorTimer;
        Timer* attackTimer;
        Timer* chaseTimer;
        PathManager* pathManager;
        std::list< Vector2<f32> > pathFollow;
        std::function<void(Unit*)> recruitedCallback;
        std::function<void(Unit*)> retractedCallback;
        Vector2<f32> vectorDes;
        Vector2<f32> vectorSpd;
        Vector2<f32> vectorDir;
        bool readyToEnter;
        const std::string attackEvent;
        const std::string moveEvent;
        const std::string selectEvent;
        std::vector< UnitFighter* > unitFighters;
        std::vector< UnitFighter* > nearUnitFighters;
        const f32 maxPositionDesviation;
        const i32 unitFighterHP;
        Sensor* unitSensor;
        UnitManager* unitManager;
};

#endif