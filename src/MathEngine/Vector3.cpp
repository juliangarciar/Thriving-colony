#include "Vector3.h"

template <class T>
Vector3<T>::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

template <class T>
Vector3<T>::Vector3(T x, T y, T z) {
    this -> x = x;
    this -> y = y;
    this -> z = z;
}

template <class T>
Vector3<T>::~Vector3() {
    
}

template <class T>
void Vector3<T>::set(T x, T y, T z) {
    this -> x = x;
    this -> y = y;
    this -> z = z;
}

template <class T>
void Vector3<T>::set(Vector3<T> v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

template <class T>
Vector3<T> Vector3<T>::normalize() {
    Vector3<T> vector;

    T length = x*x + y*y + z*z;
    length = sqrt(length);

    if(length != 0){
        vector.x = (T) x/length;
        vector.y = (T) y/length;
        vector.z = (T) y/length;
    }
    return vector;
}

template <class T>
Vector3<T> Vector3<T>::getDistanceTo(Vector3<T> other) {
    return Vector3<T>(x - other.x, y - other.y, z - other.z);
}

template <class T>
Vector3<T> Vector3<T>::rotateFromPoint(f32 r, f32 phi, f32 theta) {
    Vector3<T> point;

    // Convert to radians
    phi = phi * (PI/180);
    theta = theta * (PI/180);

    point.x = x + (r *  sinf(phi) * cosf(theta));
    point.y = y + (r * -sinf(theta));
    point.z = z + (r *  cosf(phi) * cosf(theta));

    return point;
}

template <class T>
Vector2<T> Vector3<T>::toVector2() const{
    Vector2<T> dummy;
    dummy.x = x;
    dummy.y = z;
    return dummy;
}
//      **      //

template <class T>
bool Vector3<T>::operator == (const Vector3<T> &p) const {
    return x == p.x && y == p.y && z == p.z;
}

template <class T>
bool Vector3<T>::operator != (const Vector3<T> &p) const {
    return x != p.x || y != p.y || z != p.z;
}

template <class T>
Vector3<T> Vector3<T>::operator + (const Vector3<T> &p) const {
    return Vector3<T>(x + p.x, y + p.y, z + p.z);
}

template <class T>
Vector3<T> Vector3<T>::operator + (const f32 &p) const {
    return Vector3<T>(x + p, y + p, z + p);
}

template <class T>
Vector3<T> Vector3<T>::operator - (const Vector3<T> &p) const {
    return Vector3<T>(x - p.x, y - p.y, z - p.z);
}

template <class T>
Vector3<T> Vector3<T>::operator - (const f32 &p) const {
    return Vector3<T>(x - p, y - p, z - p);
}

template <class T>
Vector3<T> Vector3<T>::operator * (const Vector3<T> &p) const {
    return Vector3<T>(x * p.x, y * p.y, z * p.z);
}

template <class T>
Vector3<T> Vector3<T>::operator * (const f32 &p) const {
    return Vector3<T>(x * p, y * p, z * p);
}

template <class T>
Vector3<T> Vector3<T>::operator / (const Vector3<T> &p) const {
    return Vector3<T>(x / p.x, y / p.y, z / p.z);
}

template <class T>
Vector3<T> Vector3<T>::operator / (const f32 &p) const {
    return Vector3<T>(x / p, y / p, z / p);
}

template class Vector3<i32>;
template class Vector3<f32>; 