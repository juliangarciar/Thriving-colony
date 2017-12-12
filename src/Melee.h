#ifndef MELEE_H
#define MELEE_H

#include "Unit.h"
#include <irrlicht.h>


class Melee : public Unit {
    
    public:

        Melee(irr::core::vector3df* vectorData);
        virtual ~Melee();

    private:

};

#endif