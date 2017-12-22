#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include "GraphicEngine/Vector3.h"
//#include "Battle.h"

#include <iostream>
#include <cmath>
class Unit : public Entity {
    
    public:
        //The consctructor is empty because the object it's constructed in the child
        Unit(int id, Vector3<float> vectorData, Enumeration::Team teamData);
        virtual ~Unit();

        //Getters
        Entity* getTarget();
        Model* getModel();

        //Setters
        void setMoving(bool);
        void setAttacking(bool);
        void setPosition(Vector3<float> vectorData);
        void setDestination(Vector3<float> vectorData);

        /////////////////////////
        void attack();
        void updateTarget();
        void moveTroop();
        void updateTroop();
        //void assignBattle(Battle*);

    protected:
        //Unit stats
        int moveSpeed;
        int attackSpeed;
        int attackDamage;
        int attackRange;
        int viewRange;

        //Action bools
        bool moving;
        bool attacking;

        //Space vectors used for unit movement
        //Vector position is in the father
        Vector3 <float> *vectorPos;
        Vector3 <float> *vectorDes;
        Vector3 <float> *vectorMov;
        
        Entity* target;
        //Unit type
        Enumeration::UnitType::SubClass type;

        //Battle* battleInvolved;

    private:
        
};

#endif