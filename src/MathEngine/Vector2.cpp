#include "Vector2.h"

template <class T>
Vector2<T>::Vector2() {
    this -> x = 0;
    this -> y = 0;
}

template <class T>
Vector2<T>::Vector2(T x, T y) {
    this -> x = x;
    this -> y = y;
}

template <class T>
Vector2<T>::Vector2(core::vector2di v) {
    this -> x = v.X;
    this -> y = v.Y;
}

template <class T>
Vector2<T>::Vector2(core::vector2df v) {
    this -> x = v.X;
    this -> y = v.Y;
}

template <class T>
Vector2<T>::~Vector2() {
    
}

template <class T>
void Vector2<T>::set(T x, T y) {
    this -> x = x;
    this -> y = y;
}

template <class T>
void Vector2<T>::set(core::vector2di v) {
    this -> x = v.X;
    this -> y = v.Y;
}

template <class T>
void Vector2<T>::set(core::vector2df v) {
    this -> x = v.X;
    this -> y = v.Y;
}

template <class T>
Vector2<T> Vector2<T>::normalize() {
    Vector2<T> vector;

    T length = x*x + y*y;
    length = sqrt(length);

    if(length != 0){
        vector.x = (T) x/length;
        vector.y = (T) y/length;
    }
    return vector;
} 

template <class T>
Vector2<T> Vector2<T>::getDistanceTo(Vector2<T> other) {
    return Vector2<T>(x - other.x, y - other.y);
}

template <class T>
Vector2<T> Vector2<T>::getFromPolarCoordinates(f32 r, f32 phi) {
    phi = phi * (PI/180);
    Vector2<T> point;
    point.x = x + (r * cosf(phi));  // Assign to the point member x
    point.y = y + (r * sinf(phi));  // Assign to the point member y.
    return point;
}

template <class T>
core::vector2di Vector2<T>::getVectorI() {
    return core::vector2di(x, y);
}

template <class T>
core::vector2df Vector2<T>::getVectorF() {
    return core::vector2df(x, y);
}

// Added by Julian
template <class T>
T Vector2<T>::calculateDistance(Vector2<T> b){
    
    T disX, disY;
    disX = this->x - b.x;
    disY = this->y - b.y;
    T distance = std::sqrt(disX * disX + disY * disY);
    return distance;
}

template <class T>
Vector2<T> Vector2<T>::operator + (const Vector2<T> &p) const {
    return Vector2<T>(this -> x + p.x, this -> y + p.y);
}
template <class T>
Vector2<T> Vector2<T>::operator - (const Vector2<T> &p) const {
    return Vector2<T>(this -> x - p.x, this -> y - p.y);
}
template <class T>
Vector2<T> Vector2<T>::operator / (const f32 &num) const {
    return Vector2<T>(this -> x / num, this -> y / num);
}

template class Vector2<i32>;
template class Vector2<f32>;