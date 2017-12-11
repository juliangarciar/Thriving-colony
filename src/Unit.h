#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include <irrlicht.h>
#include <iostream>
class Unit : public Entity {
    
    public:
      Unit(int, int, int, int, int, int, int xData, int yData, int zData, irr::scene::ISceneManager *smgr);
      virtual ~Unit();

      //Getters
      Entity *getTarget();
      irr::scene::IMeshSceneNode *getCube();
      //Setters
      void setMoving(bool);
      void setAttacking(bool);

      void setPos(irr::core::vector3df *vectorData);
      void setDes(irr::core::vector3df vectorData);
      /////////////////////////
      void attack();
      void moveTroop();
      void updateTroop();

    protected:
        int moveSpeed;
        int attackSpeed;
        int attackDamage;
        int attackRange;
        int viewRange;

        bool moving;
        bool attacking;

        irr::scene::ISceneManager *smgr;
        irr::scene::IMeshSceneNode *cube;

        irr::core::vector3df *vectorDes;
        irr::core::vector3df *vectorPos;
        irr::core::vector3df *vectorMov;

        Entity* target;
    private:
        
};

#endif