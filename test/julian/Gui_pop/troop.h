#ifndef TROOP_H
#define TROOP_H

#include <iostream>
#include <irrlicht.h>

#define PI 3.14159265

class troop{
private:
  int posX;
  int posY;
  int posZ;
  int desX;
  int desY;
  int desZ;

  float speed;
  bool mov;
  double times;

  

  irr::scene::ISceneManager *smgr;
  irr::scene::IMeshSceneNode *cube;

  irr::core::vector3df *vectorDes;
  irr::core::vector3df *vectorPos;
  irr::core::vector3df *vectorMov;
public:
  troop(int x, int y, int z, irr::scene::ISceneManager *smgrData);
  troop(const troop& orig);
  virtual ~troop();

  irr::scene::IMeshSceneNode* getCube();
  int getX();
  int getY();
  int getZ();
  void setPos(irr::core::vector3df *vectorData);
  void setDes(irr::core::vector3df vectorData);
  void moveTroop();
  void updateTroop();
};
#endif /* TROOP_H */