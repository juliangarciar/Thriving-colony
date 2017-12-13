#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include <iostream>
#include <cmath>
class Unit : public Entity {
    
    public:
        //The consctructor is empty because the object it's constructed in the child
        Unit(Vector3<float> *vectorData, bool teamData);
        virtual ~Unit();

        //Getters
        Entity* getTarget();
        Model* getModel();
        //Setters
        void setMoving(bool);
        void setAttacking(bool);

        void setPos(Vector3<float> *vectorData);
        void setDes(Vector3<float> *vectorData);
        /////////////////////////
        void attack();
        void moveTroop();
        void updateTroop();

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
        Vector3 <float> *vectorDes;
            //Vector3 <float> *vectorPos;
        Vector3 <float> *vectorMov;
        
        Entity* target;
        //Unit type
        Enumeration::UnitType::SubClass type;

      private:
        
};

#endif