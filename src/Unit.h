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
        Unit(int id, SceneNode *layer, Vector3<float> vectorData, Enumeration::Team teamData, Enumeration::UnitType typeData, Enumeration::RaceType raceData);
        virtual ~Unit();

    //Getters
        Entity* getTarget();
        Model* getModel();
        //MusicStrings
        string getAttackEvent();
        string getMoveEvent();
        string getSelectEvent();
        //Cost data -> maybe not needed (because there is an enumeration with this data)
        
        int getMetalCost();
        int getCrystalCost();
        int getHappinesCost();
    //Setters
        void setMoving(bool);
        void setAttacking(bool);
        void setTroopPosition(Vector3<float> vectorData);
        void setTroopDestination(Vector3<float> vectorData);

        /////////////////////////
        void attack();
        //void updateTarget(Entity*);
        void moveTroop();
        void updateTroop();
        //void assignBattle(Battle*);
        virtual void taxPlayer(Enumeration::Team);

        //int getAttackRange();
        
    private:
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
        // Timers
        float lookForTargetTimer;
        float lookForTargetCountdown;
        float attackCountdown;

    //Space vectors used for unit movement
        //Vector position is in the father
        Vector3 <float> *vectorPos;
        Vector3 <float> *vectorDes;
        Vector3 <float> *vectorMov;
        
        //Entity* target;
    //Unit type
        Enumeration::UnitType unitType;
        Enumeration::RaceType unitRace;
        //Battle* battleInvolved;

    //Music events to be played
        string attackEvent;
        string moveEvent;
        string selectEvent;
        
};

#endif