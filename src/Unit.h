#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include "GraphicEngine/Vector3.h"
#include <PathPlanner/PathManager.h>
//#include "Battle.h"

#include <iostream>
#include <cmath>
#include <string>
#include <list>
using namespace std;
class Unit : public Entity {
    
    public:
        //The consctructor is empty because the object it's constructed in the child
        Unit(int id, SceneNode *layer, const wchar_t *path, Vector3<float> vectorData, Enumeration::Team teamData, Enumeration::UnitType typeData, Enumeration::BreedType raceData);
        virtual ~Unit();

        //Getters
        Entity* getTarget();
        Model* getModel();
        std::list< Vector2<float> > getPath();
        //MusicStrings
        string getAttackEvent();
        string getMoveEvent();
        string getSelectEvent();
        //Cost data -> maybe not needed (because there is an enumeration with this data)
        
        int getMetalCost();
        int getCrystalCost();
        int getHappinesCost();

        bool getRetracted();
        bool getMoving();

        Vector3<float>* getDestination();
        
        //Setters
        void setMoving(bool);
        void setAttacking(bool);
        void setRetracted(bool);
        void setTroopPosition(Vector3<float> vectorData);
        void setTroopDestination(Vector3<float> vectorData);
        void setPath(std::list< Vector2<float> > path);
        void setPathToTarget(Vector3<float> vectorData);
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

        bool getReadyToEnter();
        
    private:
        Enumeration::UnitState state;
    //Unit stats
        int moveSpeed;
        int attackSpeed;
        int attackDamage;
        //int attackRange;
        int viewRange;
        //Maybe this isn't needed
        int metalCost;
        int crystalCost;
        int happinessCost;
    //Action bools
        bool moving;
        bool attacking;
        bool retracted;
        // Timers
        float lookForTargetTimer;
        float lookForTargetCountdown;
        float attackCountdown;

    //Space vectors used for unit movement
        class PathManager* pathManager;
        std::list< Vector2<float> > pathFollow;
        //Vector position is in the father
        Vector3 <float> *vectorPos;
        Vector3 <float> *vectorDes;
        Vector3 <float> *vectorMov;
        float steps;
        //Entity* target;
    //Unit type
        Enumeration::UnitType unitType;
        Enumeration::BreedType unitRace;
        //Battle* battleInvolved;

    //Music events to be played
        string attackEvent;
        string moveEvent;
        string selectEvent;
        
        bool readyToEnter;
};

#endif