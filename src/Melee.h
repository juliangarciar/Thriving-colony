#ifndef MELEE_H
#define MELEE_H

#include "Unit.h"
#include <irrlicht.h>
class Melee : public Unit {
    
    public:

        Melee(int, int, int, int, int, int, int x, int y, int z, irr::scene::ISceneManager *smgr);
        virtual ~Melee();

    private:
        
};

#endif