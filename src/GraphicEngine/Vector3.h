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
        Vector3(core::vector3di v);
        Vector3(core::vector3df v);
        virtual ~Vector3();

        void set(T x, T y, T z);
        void set(core::vector3di v);
        void set(core::vector3df v);
        void set(Vector3<T> v);

        Vector3<T>& normalize();
        T getLength();

        core::vector3di getVectorI();
        core::vector3df getVectorF();
        
        bool operator ==(const Vector3<T> &p) const;
        bool operator !=(const Vector3<T> &p) const;
        Vector3<T> operator +(const Vector3<T> &p) const;
        Vector3<T> operator +(const float &num) const;
        Vector3<T> operator -(const Vector3<T> &p) const;
        Vector3<T> operator -(const float &num) const;

    private:
};

#endif