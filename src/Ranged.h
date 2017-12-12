#ifndef RANGED_H
#define RANGED_H

#include "Unit.h"
#include <irrlicht.h>
class Ranged : public Unit {
    
    public:
      Ranged(irr::core::vector3df *vectorData);
      virtual ~Ranged();

    private:
        
};

#endif