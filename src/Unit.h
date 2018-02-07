#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include "GraphicEngine/Vector3.h"

//#include "Battle.h"

#include <iostream>
#include <cmath>
#include <string>
using namespace std;
class Unit : public Entity {
    
    public:
        //The consctructor is empty because the object it's constructed in the child
        Unit(SceneNode *layer, int id, const wchar_t *path, Enumeration::Team teamData, Enumeration::BreedType raceData, Enumeration::UnitType typeData, Vector3<float> vectorData);
        virtual ~Unit();

        /////////////////////////
        void attack();
        //void updateTarget(Entity*);
        void moveTroop();
        void attackMoveTroop();
        void chaseTarget();
        void updateTroop();
        //void assignBattle(Battle*);
        virtual void taxPlayer(Enumeration::Team);

        //int getAttackRange();
        bool inRangeOfAttack();

        // State machine
        void switchState(Enumeration::UnitState);
        void idleState();
        void moveState();
        void attackMoveState();
        void attackState();
        void chaseState();
        void retractState();
        
        bool refreshTarget();
        
        //Setters
        void setMoving(bool);
        void setAttacking(bool);
        void setRetracted(bool);
        void setTroopPosition(Vector3<float> vectorData);
        void setTroopDestination(Vector3<float> vectorData);

        //Getters
        Entity* getTarget();
        Model* getModel();

        string getAttackEvent();
        string getMoveEvent();
        string getSelectEvent();

        bool getRetracted();
        bool getMoving();
        bool getReadyToEnter();

        Vector3<float>* getDestination();
    private:
    //Init
        /**
         * @brief cosa
         */
        void Init();

    //CurrentState
        Enumeration::UnitState state;

    //Unit stats
        int moveSpeed;
        int attackSpeed;
        int attackDamage;

    // Action bools
        bool moving;
        bool attacking;
        bool retracted;

    // Timers
        float lookForTargetTimer;
        float lookForTargetCountdown;
        float attackCountdown;

    // Space vectors used for unit movement
        //Vector position is in the father
        Vector3 <float> *vectorPos;
        Vector3 <float> *vectorDes;
        Vector3 <float> *vectorMov;
        
    //Unit type
        Enumeration::UnitType unitType;
        bool readyToEnter;

    //Music events to be played
        string attackEvent;
        string moveEvent;
        string selectEvent;
};

#endif