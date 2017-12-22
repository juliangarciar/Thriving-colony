#ifndef RANGED_H
#define RANGED_H

#include "Unit.h"
#include <string>
using namespace std;
class Ranged : public Unit {
    
  public:
    //Enum: Standard, Advanced, Launcher, Desintegrator
    //teamData sepecifies the unit team and vectorData the position
    Ranged(int id, Enumeration::UnitType::SubClass unitData, Vector3<float> vectorData, Enumeration::Team teamData);
    virtual ~Ranged();
    string getAttackEvent();
    string getMoveEvent();
    string getSelectEvent();
  private:
    string attackEvent;
    string moveEvent;
    string selectEvent;
};

#endif