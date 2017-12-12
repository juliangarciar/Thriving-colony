#ifndef MELEE_H
#define MELEE_H

#include "Unit.h"
#include <irrlicht.h>


class Melee : public Unit {
    
    public:

        Melee(irr::core::vector3df* vectorData);
        Melee(int, Vector3<float>*, int, int, int, int, int, bool, Box3D<float>*, Model*);
        virtual ~Melee();

    private:

};

#endif