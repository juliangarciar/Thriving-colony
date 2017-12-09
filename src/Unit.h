#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"


class Unit : public Entity {
    
    public:
        Unit(int, int, int, int, int, int);
        virtual ~Unit();

        //Getters
        Entity *getTarget();

        //Setters
        void setMoving(bool);
        void setAttacking(bool);

        /////////////////////////
        void attack();

    protected:

        int moveSpeed;
        int attackSpeed;
        int attackDamage;
        int attackRange;
        int viewRange;

        bool moving;
        bool attacking;


        Entity* target;
    private:
        
};

#endif