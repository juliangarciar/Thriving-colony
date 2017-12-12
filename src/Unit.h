#ifndef UNIT_H
#define UNIT_H

#include "Entity.h"
#include "GraphicEngine/Vector3.h"
#include "GraphicEngine/Model.h"
#include <iostream>
#include <irrlicht.h>

class Unit : public Entity {
    
    public:
      Unit(irr::core::vector3df *vectorData);
      virtual ~Unit();

      //Getters
      Entity* getTarget();
      Model* getModel();
      //Setters
      void setMoving(bool);
      void setAttacking(bool);

      void setPos(irr::core::vector3df *vectorData);
      void setDes(irr::core::vector3df *vectorData);
      /////////////////////////
      void attack();
      void moveTroop();
      void updateTroop();

    protected:
        //Unit stats
        int moveSpeed;
        int attackSpeed;
        int attackDamage;
        int attackRange;
        int viewRange;

        //Action bools
        bool moving;
        bool attacking;

        //Graphic engine
        //irr::scene::ISceneManager *smgr;
        //irr::scene::IMeshSceneNode *cube;
        Model *unitModel;
        //Space vectors used for unit movement
        irr::core::vector3df *vectorDes;
        irr::core::vector3df *vectorPos;
        irr::core::vector3df *vectorMov;

        
        Entity* target;
    private:
        
};

#endif