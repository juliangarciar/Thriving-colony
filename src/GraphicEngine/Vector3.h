#ifndef VECTOR3_H
#define VECTOR3_H

#include <irrlicht.h>

using namespace irr;

template <class T>
class Vector3 {

    public:
        Vector3(T x, T y, T z);
        virtual ~Vector3();

        Vector3 getVector();
        core::vector3di getVectorI();
        core::vector3df getVectorF();
        
    private:
        T x, y, z;
};

#endif