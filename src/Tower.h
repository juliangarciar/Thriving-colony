#ifndef TOWER_H
#define TOWER_H

#include "Building.h"

class Tower : public Building {
    
    public:
<<<<<<< HEAD
      Tower(Vector3<float> *vectorData, Enumeration::Team teamData);
=======
      Tower(SceneNode *parent, Vector3<float> *vectorData, bool teamData);
>>>>>>> GraphicEngine
      virtual ~Tower();
    
    private:
      int attackSpeed;
      int damage;

      Entity *objetive;
};

#endif