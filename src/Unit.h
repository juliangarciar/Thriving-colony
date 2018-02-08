#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include <GraphicEngine/Vector3.h>
#include <PathPlanner/PathManager.h>

#include <iostream>
#include <functional>
#include <cmath>
#include <string>
#include <list>

class Unit : public Entity {
    
    public:
        //The consctructor is empty because the object it's constructed in the child
        Unit(SceneNode *layer, int id, const wchar_t *path, Enumeration::Team teamData, Enumeration::BreedType raceData, Enumeration::UnitType typeData, Vector3<float> vectorData);
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
        void setTroopPosition(Vector3<float> vectorData);
        void setTroopDestination(Vector3<float> vectorData);
        void setPath(std::list< Vector2<float> > path);
        void setPathToTarget(Vector3<float> vectorData);
        void setRecruitedCallback(std::function<void(Unit*)>);
        void setRetractedCallback(std::function<void(Unit*)>);

        //Getters
        std::string getAttackEvent();
        std::string getMoveEvent();
        std::string getSelectEvent();

        Vector3<float>* getDestination();
        std::list< Vector2<float> > getPath();
    private:
    //Init
        /**
         * @brief inicia
         */
        void Init();

    // CurrentState
        Enumeration::UnitState state;

    // Unit type
        Enumeration::UnitType unitType;

    // Unit stats
        int moveSpeed;
        int attackSpeed;
        int attackDamage;

    // Action bools
        bool finished;
        bool moving;
        bool attacking;

    // Unit info
        float recruitingTime;

    // Timers
        float recruitingTimer;
        float lookForTargetTimer;
        float lookForTargetCountdown;
        float attackCountdown;

    // Space vectors used for unit movement
        class PathManager* pathManager;
        std::list< Vector2<float> > pathFollow;

    //Finish recruiting callback
        std::function<void(Unit*)> recruitedCallback;
        std::function<void(Unit*)> retractedCallback;

    // Vector position is in the father
        Vector3 <float> *vectorPos;
        Vector3 <float> *vectorDes;
        Vector3 <float> *vectorMov;
        float steps;

    // Algo
        bool readyToEnter;

    // Music events to be played
        std::string attackEvent;
        std::string moveEvent;
        std::string selectEvent;
};

#endif