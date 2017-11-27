#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Unit : public Entity {
    
    public:
        Unit(int, int, int, int, int, int);
        virtual ~Unit();

        //Getters
        Entity *getObjetive();

        //Setters
        void setMoving(bool);
        void setAttacking(bool);

        /////////////////////////
        void attack();

    protected:
        int moveSpeed;
        int attackSpeed;
        int damage;
        int attackRange;
        int viewRange;

        bool moving;
        bool attacking;

        Entity *objetive;

        Entity* target;
    private:
        
};

#endif