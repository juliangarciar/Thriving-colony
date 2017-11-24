#ifndef VECTOR3_H
#define VECTOR3_H

#include <irrlicht.h>

using namespace irr;

template <class T>
class Vector3 {

    public:
        T x, y, z;
        
        Vector3();
        Vector3(T x, T y, T z);
        virtual ~Vector3();

        void setPosition(T x, T y, T z);
        void setPosition(core::vector3di position);
        void setPosition(core::vector3df position);

        Vector3<T>& normalize();

        core::vector3di getVectorI();
        core::vector3df getVectorF();
        
    private:
};

#endif