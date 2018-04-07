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
#include <IOEngine/Timer.h>

class Troop;
class Unit : public Entity {
    
    public:
        //The consctructor is empty because the object it's constructed in the child
        Unit(SceneNode *, i32, Enumeration::Team, Enumeration::BreedType, Enumeration::UnitType);
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
        void setUnitCell(Vector2<f32> vectorPosition);
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

        Vector3<f32> getDestination();
        std::list< Vector2<f32> > getPath();
        Enumeration::UnitType getType();

        Enumeration::UnitState getState();
    private:
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
        //f32 recruitingTime;

        // Timers
        Timer* recruitingTimer;
        Timer* lookForTargetTimer;
        f32 lookForTargetCountdown;
        // Esto que?
        f32 attackCountdown;

        // Scene Node
        SceneNode *layer;

        // Space vectors used for unit movement
        class PathManager* pathManager;
        std::list< Vector2<f32> > pathFollow;

        //Finish recruiting callback
        std::function<void(Unit*)> recruitedCallback;
        std::function<void(Unit*)> retractedCallback;

        // Vector position is in the father
        Vector3 <f32> vectorPos;
        Vector3 <f32> vectorDes;
        Vector3 <f32> vectorMov;
        f32 steps;

        // Stuff
        bool readyToEnter;

        // Music events to be played
        std::string attackEvent;
        std::string moveEvent;
        std::string selectEvent;

        /* Juli troops */
        Troop* troops;
};

#endif