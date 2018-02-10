#ifndef TROOP_H
#define TROOP_H

#include <iostream>
#include <irrlicht.h>

#define PI 3.14159265

class troop{
private:
  i32 posX;
  i32 posY;
  i32 posZ;
  i32 desX;
  i32 desY;
  i32 desZ;

  f32 speed;
  bool mov;
  double times;

  

  irr::scene::ISceneManager *smgr;
  irr::scene::IMeshSceneNode *cube;

  irr::core::vector3df *vectorDes;
  irr::core::vector3df *vectorPos;
  irr::core::vector3df *vectorMov;
public:
  troop(i32 x, i32 y, i32 z, irr::scene::ISceneManager *smgrData);
  troop(const troop& orig);
  virtual ~troop();

  irr::scene::IMeshSceneNode* getCube();
  i32 getX();
  i32 getY();
  i32 getZ();
  void setPos(irr::core::vector3df *vectorData);
  void setDes(irr::core::vector3df vectorData);
  void moveTroop();
  void updateTroop();
};
#endif /* TROOP_H */