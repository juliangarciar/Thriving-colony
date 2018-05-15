#ifndef VECTOR3_H
#define VECTOR3_H

#include "Vector2.h"
#include <irrlicht/irrlicht.h>
#include "../Types.h"

#include <irrlicht/irrlicht.h>
#include <glm/vec3.hpp>

#define PI 3.14159265

template <class T>
class Vector3 {
    public:
        T x, y, z;
        
        Vector3();
        Vector3(T x, T y, T z);
        virtual ~Vector3();

        void set(T x, T y, T z);
        void set(Vector3<T> v);

        Vector3<T> normalize();
        Vector3<T> rotateFromPoint(f32 r, f32 phi, f32 theta);
        Vector3<T> getDistanceTo(Vector3<T> other);

        Vector2<T> toVector2() const;
        
        bool operator ==(const Vector3<T> &p) const;
        bool operator !=(const Vector3<T> &p) const;
        Vector3<T> operator +(const Vector3<T> &p) const;
        Vector3<T> operator +(const f32 &num) const;
        Vector3<T> operator -(const Vector3<T> &p) const;
        Vector3<T> operator -(const f32 &num) const;
        Vector3<T> operator *(const Vector3<T> &p) const;
        Vector3<T> operator *(const f32 &num) const;
        Vector3<T> operator /(const Vector3<T> &p) const;
        Vector3<T> operator /(const f32 &num) const;
/*
        //Irrlicht
        Vector3(irr::core::vector3di v);
        Vector3(irr::core::vector3df v);
        void set(irr::core::vector3di v);
        void set(irr::core::vector3df v);
        irr::core::vector3di getVectorI();
        irr::core::vector3df getVectorF();

        //glm
        Vector3(glm::vec3 v);
        void set(glm::vec3 v);
        glm::vec3 getVec3();
*/
    private:
};

template<class T> inline std::ostream& operator<<(std::ostream& out, const Vector3<T>& val){
    out << "x: " << val.x << " y " << val.y << " z " << val.z;
    return out;
}

#endif