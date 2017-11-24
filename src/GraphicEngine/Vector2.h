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
        virtual ~Vector2();

        void setPosition(T x, T y);
        void setPosition(core::vector2di position);
        void setPosition(core::vector2df position);

        Vector2<T>& normalize();

        core::vector2di getVectorI();
        core::vector2df getVectorF();
        
    private:
};

#endif