#ifndef UNIT_H
#define UNIT_H

#include <functional>
#include <cmath>
#include <string>
#include <list>
#include <Types.h>
#include <Entity.h>
#include <MathEngine/Vector3.h>
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
         * @param SceneNode is the layer where the unit is going to be created.
         * @param id32 is the id number that will identify the unit.
         * @param Enumeration::Team is the team to which belongs the building: Enumeration::Team::Human or Enumeration::Team::IA. 
         * @param UnitData is the data for this unit
         */
        Unit(SceneNode* _layer, 
            i32 _id, 
            Enumeration::Team _team, 
            baseUnit baseData):Entity(_layer,
                                    _id,
                                    _team,
                                    Enumeration::EntityType::Unit,
                                    baseData.maxHP,
                                    baseData.viewRadious,
                                    baseData.attackRange,
                                    baseData.metalCost,
                                    baseData.crystalCost,
                                    baseData.happines,
                                    baseData.citizens,
                                    1,
                                    1,
                                    baseData.modelPath,
                                    baseData.texturePath
                                    ):
                                    state(Enumeration:UnitState::Recruiting),
                                    moveSpeed(baseData.moveSpeed),
                                    attackSpeed(baseData.attackSpeed),
                                    attackDamage(baseData.attackDamage),
                                    finished(false),
                                    moving(false),
                                    attacking(false),
                                    armyLevel(baseData.armyLevel),
                                    citizens(baseData.citizens),
                                    pathFollow(),
                                    vectorDes(0,0),
                                    vectorMov(0,0),
                                    steps(0),
                                    attackEvent(baseData.attackEvent),
                                    moveEvent(baseData.moveEvent),
                                    selectEvent(baseData.selectEvent),
                                    attackCountdown(0),
                                    readyToEnter(false)
        {
            lookForTargetTimer = new Timer (0.5, true);
            lookForTargetTimer -> setCallback([&](){
                // Ask for a new target
                Game::Instance() -> getGameState() -> getBattleManager() -> askForTarget(this); //ToDo: La hipocresia
            });

            recruitingTimer = new Timer(0, false);
            recruitingTimer -> setCallback([&](){
                recruitedCallback(this);
                switchState(Enumeration::UnitState::InHome);
            });
            pathManager = new PathManager(this);
        };
        
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
         * @brief Finish retracting the unit
         */
        void triggerRetractedCallback();

        //Setters
        void setUnitCell(Vector2<f32> vectorPosition);
        void setMoving(bool);
        void setAttacking(bool);
        void setTroopPosition(Vector2<f32> vectorData);
        void setTroopDestination(Vector2<f32> vectorData);
        void setPath(std::list< Vector2<f32> > path);
        void setPathToTarget(Vector2<f32> vectorData);
        void setRecruitedCallback(std::function<void(Unit*)>);
        void setRetractedCallback(std::function<void(Unit*)>);

        //Getters
        std::string getAttackEvent();
        std::string getMoveEvent();
        std::string getSelectEvent();

        Vector2<f32> getDestination();
        std::list< Vector2<f32> > getPath();
        std::string getType();

        Enumeration::UnitState getState();

        /**
         * @breif Get the army level that the entity provides to the player's city.
         * @return i32 that will be the value of the armyLevel variable.
         */
        i32 getArmyLevel();
    private:
        /**
         * @brief inicia
         */
        void Init();

        // CurrentState
        Enumeration::UnitState state;

        // Unit type
        std::string type;

        // Unit stats
        i32 moveSpeed;
        i32 attackSpeed;
        i32 attackDamage;

        // Action bools
        bool finished;
        bool moving;
        bool attacking;

        // Unit info
        //f32 recruitingTime;
        i32 armyLevel; //ToDo: explicar para que sirve esto
        i32 citizens;

        // Timers
        Timer* recruitingTimer;
        Timer* lookForTargetTimer;
        f32 lookForTargetCountdown;
        // Esto que?
        f32 attackCountdown;

        // Scene Node
        SceneNode *layer;

        // Space vectors used for unit movement
        PathManager* pathManager;
        std::list< Vector2<f32> > pathFollow;

        //Finish recruiting callback
        std::function<void(Unit*)> recruitedCallback;
        std::function<void(Unit*)> retractedCallback;

        // Vector position is in the father
        //Vector2<f32> vectorPos;
        Vector2<f32> vectorDes;
        Vector2<f32> vectorMov;
        f32 steps;

        // Stuff
        bool readyToEnter;

        // Music events to be played
        std::string attackEvent;
        std::string moveEvent;
        std::string selectEvent;

        Troop* troops;
};

#endif