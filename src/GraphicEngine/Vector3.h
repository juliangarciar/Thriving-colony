#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <irrlicht.h>
<<<<<<< HEAD
#include "Vector2.h"
=======

#define PI 3.14159265

>>>>>>> master
using namespace irr;

template <class T>
class Vector3 {

    public:
        T x, y, z;
        
        Vector3();
        Vector3(T x, T y, T z);
        Vector3(core::vector3di v);
        Vector3(core::vector3df v);
        virtual ~Vector3();

        void set(T x, T y, T z);
        void set(core::vector3di v);
        void set(core::vector3df v);
        void set(Vector3<T> v);

<<<<<<< HEAD
        Vector3<T>& normalize();
    // Added by Julian
        Vector2<T> toVector2();
        // ** //
        T getLength();
=======
        Vector3<T> normalize();
        Vector3<T> getDistanceTo(Vector3<T> other);
        Vector3<T> rotateFromPoint(float r, float phi, float theta);
>>>>>>> master

        core::vector3di getVectorI();
        core::vector3df getVectorF();
        
        bool operator ==(const Vector3<T> &p) const;
        bool operator !=(const Vector3<T> &p) const;
        Vector3<T> operator +(const Vector3<T> &p) const;
        Vector3<T> operator +(const float &num) const;
        Vector3<T> operator -(const Vector3<T> &p) const;
        Vector3<T> operator -(const float &num) const;
        Vector3<T> operator *(const Vector3<T> &p) const;
        Vector3<T> operator *(const float &num) const;
        Vector3<T> operator /(const Vector3<T> &p) const;
        Vector3<T> operator /(const float &num) const;

    private:
};

template<class T> inline std::ostream& operator<<(std::ostream& out, const Vector3<T>& val){
    out << "x: " << val.x << " y " << val.y << " z " << val.z;
    return out;
}

#endif