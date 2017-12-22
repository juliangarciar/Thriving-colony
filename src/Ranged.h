#ifndef RANGED_H
#define RANGED_H

#include "Unit.h"

class Ranged : public Unit {
    
  public:
    //Enum: Standard, Advanced, Launcher, Desintegrator
    //teamData sepecifies the unit team and vectorData the position
    Ranged(Enumeration::UnitType::SubClass unitData, Vector3<float> vectorData, Enumeration::Team teamData);
    virtual ~Ranged();

  private:
};

#endif