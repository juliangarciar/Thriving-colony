#ifndef TOWER_H
#define TOWER_H

#include "Building.h"

class Tower : public Building {
    
    public:
        Tower(int, int, int);
        virtual ~Tower();
    
    private:
      int attackSpeed;
      int damage;  
};

#endif