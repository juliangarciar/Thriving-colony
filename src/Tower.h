#ifndef TOWER_H
#define TOWER_H

#include "Building.h"

class Tower : public Building {
    
    public:
      Tower(Vector3<float> *vectorData, Enumeration::Team teamData, Model *modelData, Box3D<float> *boxData);
      virtual ~Tower();
    
    private:
      int attackSpeed;
      int damage;

      Entity *objetive;
};

#endif