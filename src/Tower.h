#ifndef TOWER_H
#define TOWER_H

#include "Building.h"

class Tower : public Building {
    
    public:
      Tower(SceneNode *parent, Vector3<float> *vectorData, bool teamData);
      virtual ~Tower();
    
    private:
      int attackSpeed;
      int damage;

      Entity *objetive;
};

#endif