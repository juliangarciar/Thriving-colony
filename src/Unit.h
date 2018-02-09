#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include <GraphicEngine/Vector3.h>
#include <PathPlanner/PathManager.h>
#include <Types.h>

#include <iostream>
#include <functional>
#include <cmath>
#include <string>
#include <list>

class Unit : public Entity {
    
    public:
        //The consctructor is empty because the object it's constructed in the child
        Unit(SceneNode *layer, i32 id, const wchar_t *path, Enumeration::Team teamData, Enumeration::BreedType raceData, Enumeration::UnitType typeData, Vector3<f32> vectorData);
        virtual ~Unit();

        // Game
        virtual void preTaxPlayer();
        virtual void posTaxPlayer();
        void update();

        // Agro methods
        void attack();
        void moveTroop();
        void attackMoveTroop();
        void chaseTarget();
        bool refreshTarget();
        bool inRangeOfAttack();

        bool isMoving(); 

        // State machine
        void switchState(Enumeration::UnitState);
        void recruitingState();
        void inHomeState();
        void idleState();
        void moveState();
        void attackMoveState();
        void attackState();
        void chaseState();
        void retractState();
        void triggerRecruitedCallback();
        void triggerRetractedCallback();

        //Setters
        void setMoving(bool);
        void setAttacking(bool);
        void setTroopPosition(Vector3<f32> vectorData);
        void setTroopDestination(Vector3<f32> vectorData);
        void setPath(std::list< Vector2<f32> > path);
        void setPathToTarget(Vector3<f32> vectorData);
        void setRecruitedCallback(std::function<void(Unit*)>);
        void setRetractedCallback(std::function<void(Unit*)>);

        //Getters
        std::string getAttackEvent();
        std::string getMoveEvent();
        std::string getSelectEvent();

        Vector3<f32>* getDestination();
        std::list< Vector2<f32> > getPath();
        Enumeration::UnitType getType();
    private:
    //Init
        /**
         * @brief inicia
         */
        void Init();

    // CurrentState
        Enumeration::UnitState state;

    // Unit type
        Enumeration::UnitType type;

    // Unit stats
        i32 moveSpeed;
        i32 attackSpeed;
        i32 attackDamage;

    // Action bools
        bool finished;
        bool moving;
        bool attacking;

    // Unit info
        f32 recruitingTime;

    // Timers
        f32 recruitingTimer;
        f32 lookForTargetTimer;
        f32 lookForTargetCountdown;
        f32 attackCountdown;

    // Space vectors used for unit movement
        class PathManager* pathManager;
        std::list< Vector2<f32> > pathFollow;

    //Finish recruiting callback
        std::function<void(Unit*)> recruitedCallback;
        std::function<void(Unit*)> retractedCallback;

    // Vector position is in the father
        Vector3 <f32> *vectorPos;
        Vector3 <f32> *vectorDes;
        Vector3 <f32> *vectorMov;
        f32 steps;

    // Algo
        bool readyToEnter;

    // Music events to be played
        std::string attackEvent;
        std::string moveEvent;
        std::string selectEvent;
};

#endif