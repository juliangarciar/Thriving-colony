#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Unit : public Entity {
    
    public:
        Unit(int, int, int, int);
        virtual ~Unit();

        void attack();
        void updateTarget(Entity*);

    protected:
        int moveSpeed;
        int attackSpeed;
        int attackDamage;

        Entity* target;
    private:
        
};

#endif