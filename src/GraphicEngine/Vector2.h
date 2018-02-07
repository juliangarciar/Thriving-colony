#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>
#include <irrlicht.h>

#define PI 3.14159265

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

        Vector2<T> normalize();
        Vector2<T> getDistanceTo(Vector2<T> other);
        Vector2<T> getFromPolarCoordinates(float r, float phi);

        Vector2<T> getFixed();

        core::vector2di getVectorI();
        core::vector2df getVectorF();
    // Added by Julian
        T calculateDistance(Vector2<T> b);
        Vector2<T> operator +(const Vector2<T> &p) const;
        Vector2<T> operator -(const Vector2<T> &p) const;
        Vector2<T> operator /(const float &num) const;
    private:
};

template<class T> inline std::ostream& operator<<(std::ostream& out, const Vector2<T>& val){
    out << "x: " << val.x << " y " << val.y;
    return out;
}

#endif