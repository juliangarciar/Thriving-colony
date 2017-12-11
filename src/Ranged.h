#ifndef RANGED_H
#define RANGED_H

#include "Unit.h"
#include <irrlicht.h>
class Ranged : public Unit {
    
    public:
        Ranged(int, int, int, int, int, int, int, int , int, irr::scene::ISceneManager *smgr);
        virtual ~Ranged();

    private:
        
};

#endif