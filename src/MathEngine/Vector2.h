#ifndef VECTOR2_H
#define VECTOR2_H

#include "../Types.h"

#include <irrlicht/irrlicht.h>
#include <glm/vec2.hpp>

#define PI 3.14159265

template <class T>
class Vector2 {
    public:
        T x, y;

        Vector2();
        Vector2(T x, T y);
        virtual ~Vector2();

        void set(T x, T y);

        Vector2<T> normalize();
        Vector2<T> getDistanceTo(Vector2<T> other);
        Vector2<T> getFromPolarCoordinates(f32 r, f32 phi);
        T dotProduct();
        T calculateDistance(Vector2<T> b);

        Vector2<T> operator +(const Vector2<T> &p) const;
        Vector2<T> operator +(const f32 &num) const;
        Vector2<T> operator -(const Vector2<T> &p) const;
        Vector2<T> operator /(const f32 &num) const;
        Vector2<T> operator *(const f32 &num) const;
        Vector2<T> operator +=(const Vector2<T> &p);
        bool operator ==(const Vector2<T> &p);
        bool operator !=(const Vector2<T> &p);
};

template<class T> inline std::ostream& operator<<(std::ostream& out, const Vector2<T>& val){
    out << "x: " << val.x << " y " << val.y;
    return out;
}

#endif