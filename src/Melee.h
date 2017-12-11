#ifndef MELEE_H
#define MELEE_H

#include "Unit.h"

class Melee : public Unit {
    
    public:

        Melee(int, Vector3<float>*, int, int, int, int, int, bool, Box3D<float>*, Model*);
        virtual ~Melee();

    private:
        
};

#endif