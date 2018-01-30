#ifndef TOWER_H
#define TOWER_H

#include "Building.h"

class Tower : public Building {
    
    public:
      Tower(int id, SceneNode *parent, const wchar_t *path, Vector3<float> vectorData, Enumeration::Team teamData);
      virtual ~Tower();
    
    private:
      int attackSpeed;
      int damage;

      Entity *objetive;
};

#endif