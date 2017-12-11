#ifndef RANGED_H
#define RANGED_H

#include "Unit.h"

class Ranged : public Unit {
    
    public:
        Ranged(int, Vector3<float>*, int, int, int, int, int, bool, Box3D<float>*, Model*);
        virtual ~Ranged();

    private:
        
};

#endif