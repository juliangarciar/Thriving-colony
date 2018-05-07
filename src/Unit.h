#ifndef UNIT_H
#define UNIT_H


#include <string>
#include <list>
#include <Types.h>
#include <Entity.h>
#include <PathPlanner/PathManager.h>
#include <Troop.h>
#include <EntityData.h>
#include <Enumeration.h>

//class PathManager;
//class Troop;

/**
 * @class Unit.
 * @brief Create a Unit type object. Public heritage from Entity class.
 */
class Unit : public Entity {
    
    public:
        /**
         * @brief Unit constructor.
         * 
         * @param SceneNode is the layer where the unit is going to be created.
         * @param i32 is the id number that will identify the unit.
         * @param Enumeration::Team is the team to which belongs the building: Enumeration::Team::Human or Enumeration::Team::IA. 
         * @param UnitData is the data for this unit.
         */
        Unit(SceneNode* _layer, i32 _id, Enumeration::Team _team, UnitData baseData);
        
        /**
         * @brief Unit destructor.
         */
        virtual ~Unit();

        /**
         * @brief Decrease the metal and crystal cost of the unit to the player's mteal and crystal amount and increase player's happiness, citizens and army level depending of the values of the unit.
         */
        virtual void preTaxPlayer();

        /**
         * #brief Increase the palyer's army size.
         */
        virtual void posTaxPlayer();

        /**
         * @brief Update the troop depending of its state.
        */
        void update();

        /**
         * @brief Attack the target if it is not nullptr and when the attackCountdown variable is 0 or less.
         */
        void attack();

        /**
         * @brief Move the unit.
         */
        void moveTroop();

        /**
         * @brief Chase the target when it is at range of vision of the unit and it is not at range of attack of the unit.
         */
        void chaseTarget();

        /**
         * @brief Look fora new target for the unit.
         * @return True when the unit has a target and false in other case.
         */
        bool refreshTarget();

        /**
         * @brief Determinate if the target of the unit is in its range of attack.
         * @return True when the target is in the range of attack of the unit and false in other case. 
         */
        bool inRangeOfAttack();

        /**
         * @breif Switch the current state of the unit to the state passed by parameter.
         * @param Enumeration::UnitState is the new state of the unit.
         */
        void switchState(Enumeration::UnitState);

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::Recruiting.
         */
        void recruitingState();

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::Idle.
         */
        void idleState();

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::Move.
         */
        void moveState();

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::AttackMove.
         */
        void attackMoveState();

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::Attack.
         */
        void attackState();

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::Chase.
         */
        void chaseState();

        /**
         * @brief Update the unit when its state is Enumeration::UnitState::Retract.
         */
        void retractState();

        /**
         * @brief Finish recruiting the unit.
         */
        void triggerRecruitedCallback();

        /**
         * @brief Finish retracting the unit.
         */
        void triggerRetractedCallback();

        /**
         * @brief 
         * 
         * @param
         */
        void setUnitCell(Vector2<f32>);

        /**
         * @brief Set to true or false moving variable.
         * 
         * @param True when the unit is walking and false in other case.
         */
        void setMoving(bool);

        /**
         * @brief Set to true or false attacking variable.
         * 
         * @param True when the unit is attacking to its target and false in other case.
         */
        void setAttacking(bool);

        /**
         * @brief Set the position of the unit.
         * 
         * @param The Vector2 is the position that is going to be assigned to the unit.
         */
        void setTroopPosition(Vector2<f32>);

        /**
         * @brief Set the position where the unit is going to walk to.
         * 
         * @param The Vector2 is the destination that is going to be assigned to the unit.
         */
        void setTroopDestination(Vector2<f32>);

        /**
         * @brief
         * 
         * @param
         */
        void setPath(std::list<Vector2<f32> >);

        /**
         * @brief
         * 
         * @param
         */
        void setPathToTarget(Vector2<f32>);

        /**
         * @brief
         * 
         * @param
         */
        void setRecruitedCallback(std::function<void(Unit*)>);

        /**
         * @brief
         * 
         * @param
         */
        void setRetractedCallback(std::function<void(Unit*)>);

        /**
         * @brief 
         * 
         * @return
         */
        std::string getAttackEvent();

        /**
         * @brief 
         * 
         * @return
         */
        std::string getMoveEvent();

        /**
         * @brief 
         * 
         * @return
         */
        std::string getSelectEvent();

        /**
         * @brief Get the destination of the unit.
         * 
         * @return Vector2 that will be the value of vectorDes variable.
         */
        Vector2<f32> getDestination();

        /**
         * @brief 
         * 
         * @return
         */
        std::list< Vector2<f32> > getPath();
        
        /**
         * @brief Get the type of unit of the troop.
         * 
         * @return std::string that will be the value of type variable.
         */
        std::string getType();

        /**
         * @brief Get the current state of the unit.
         * 
         * @return Enumeration::UnitState that will be the value of state variable.
         */
        Enumeration::UnitState getState();

        /**
         * @breif Get the army level that the unit provides to the player's city.
         * @return i32 that will be the value of the armyLevel variable.
         */
        i32 getArmyLevel();
        /* New */
        std::vector< Vector2<f32> > getTroopsPosition();        
    private:
        /**
         * @brief Initialize the variables.
         */
        void Init();

        //Current state of the unit that will conditione its actions.
        Enumeration::UnitState state;

        //Type of the unit.
        std::string type;

        //Speed with which the unit moves.
        i32 moveSpeed;

        //Speed with which the unit attacks.
        i32 attackSpeed;

        //Damage infliceted by the unit.
        i32 attackDamage;

        //True when the unit is trained and false in other case.
        bool finished;

        //True when the unit is moving and false in other case.
        bool moving;

        //True when the unit is attacking and false in other case.
        bool attacking;

        //Amount of army level that provides to the player's city.
        i32 armyLevel;

        //Timer that controls the time of training of the unit.
        Timer* recruitingTimer;

        //Timer that controls the time that has to pass since the last time that the unit looked for a new target.
        Timer* lookForTargetTimer;

        //Timer that controls the time that has to pass since the last time that the unit attack its target.
        f32 attackCountdown;

        //
        class PathManager* pathManager;

        //
        std::list< Vector2<f32> > pathFollow;

        //Method to finish the training of the unit.
        std::function<void(Unit*)> recruitedCallback;

        //Method to finish of retracting the unit.
        std::function<void(Unit*)> retractedCallback;

        //Destination of the unit.
        Vector2<f32> vectorDes;

        //
        Vector2<f32> vectorMov;

        //
        f32 steps;

        //True when the unit is ready to get into the command center and false in other case.
        bool readyToEnter;

        //
        std::string attackEvent;

        //
        std::string moveEvent;

        //
        std::string selectEvent;

        //
        Troop* troops;
};

#endif