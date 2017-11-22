#ifndef VECTOR3_H
#define VECTOR3_H

#include <irrlicht.h>

using namespace irr;

template <class T>
class Vector3 {

    public:
        Vector3();
        virtual ~Vector3();

        core::vector3df getVector();
        
    private:
        T x, y, z;
};

#endif