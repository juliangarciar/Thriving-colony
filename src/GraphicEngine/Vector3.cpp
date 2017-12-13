#include "Vector3.h"

template <class T>
Vector3<T>::Vector3() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

template <class T>
Vector3<T>::Vector3(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <class T>
Vector3<T>::Vector3(core::vector3di v){
    this->x = v.X;
    this->y = v.Y;
    this->z = v.Z;
}

template <class T>
Vector3<T>::Vector3(core::vector3df v){
    this->x = v.X;
    this->y = v.Y;
    this->z = v.Z;
}

template <class T>
Vector3<T>::~Vector3() {
    
}

template <class T>
void Vector3<T>::set(T x, T y, T z){
    this->x = x;
    this->y = y;
    this->z = z;
}

template <class T>
void Vector3<T>::set(core::vector3di v){
    this->x = v.X;
    this->y = v.Y;
    this->z = v.Z;
}

template <class T>
void Vector3<T>::set(core::vector3df v){
    this->x = v.X;
    this->y = v.Y;
    this->z = v.Z;
}

template <class T>
void Vector3<T>::set(Vector3<T> v){
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

template <class T>
core::vector3di Vector3<T>::getVectorI() {
    return core::vector3di(x, y, z);
}

template <class T>
core::vector3df Vector3<T>::getVectorF() {
    return core::vector3df(x, y, z);
}

template <class T>
Vector3<T>& Vector3<T>::normalize() {
    f64 length = x*x + y*y + z*z;
    // this check isn't an optimization but prevents getting NAN in the sqrt.
    if (length == 0) return *this;
        
    length = core::reciprocal_squareroot(length);

    x = (T)(x * length);
    y = (T)(y * length);
    z = (T)(z * length);
    return *this;
}

template <class T>
T Vector3<T>::getLength() {
    return core::squareroot(x*x + y*y + z*z);
}

template <class T>
bool Vector3<T>::operator == (const Vector3<T> &p) const {
    return this->x == p.x && this->y == p.y && this->z == p.z;
}

template <class T>
bool Vector3<T>::operator != (const Vector3<T> &p) const {
    return this->x != p.x || this->y != p.y || this->z != p.z;
}

template <class T>
Vector3<T> Vector3<T>::operator + (const Vector3<T> &p) const {
    return Vector3<T>(this->x+p.x, this->y+p.y, this->z+p.z);
}

template <class T>
Vector3<T> Vector3<T>::operator + (const float &p) const {
    return Vector3<T>(this->x+p, this->y+p, this->z+p);
}

template <class T>
Vector3<T> Vector3<T>::operator - (const Vector3<T> &p) const {
    return Vector3<T>(this->x-p.x, this->y-p.y, this->z-p.z);
}

template <class T>
Vector3<T> Vector3<T>::operator - (const float &p) const {
    return Vector3<T>(this->x-p, this->y-p, this->z-p);
}

template class Vector3<int>;
template class Vector3<float>; 