#ifndef VECTOR2_H
#define VECTOR2_H

#include <irrlicht.h>

using namespace irr;

template <class T>
class Vector2 {
    public:
        T x, y;

        Vector2();
        Vector2(T x, T y);
        Vector2(core::vector2di v);
        Vector2(core::vector2df v);
        virtual ~Vector2();

        void set(T x, T y);
        void set(core::vector2di v);
        void set(core::vector2df v);

        Vector2<T>& normalize();
        Vector2<T> getFromPolarCoordinates(float r, float phi);

        core::vector2di getVectorI();
        core::vector2df getVectorF();
        
    private:
};

#endif