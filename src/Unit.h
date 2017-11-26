#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"

class Unit : public Entity {
    
    public:
        Unit(int, int, int, int);
        virtual ~Unit();

    protected:
        int moveSpeed;
        int attackSpeed;
        int damage;

    private:
        
};

#endif