#ifndef TOWER_H
#define TOWER_H

#include "Building.h"

class Tower : public Building {
    
    public:
        Tower(int, int, int, Vector3<float>*, bool, Box3D<float>*, Model*);
        virtual ~Tower();
    
    private:
      int attackSpeed;
      int damage;

      Entity *objetive;
};

#endif