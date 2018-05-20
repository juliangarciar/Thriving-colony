#include "Vector2.h"

template <class T>
Vector2<T>::Vector2() {
    x = 0;
    y = 0;
}

template <class T>
Vector2<T>::Vector2(T x, T y) {
    this -> x = x;
    this -> y = y;
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
Vector2<T> Vector2<T>::normalize() {
    Vector2<T> vector;

    T length = x*x + y*y;
    length = sqrt(length);

    if (length != 0) {
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
T Vector2<T>::dotProduct() {
    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

template <class T>
T Vector2<T>::calculateDistance(Vector2<T> b) {
    
    T disX, disY;
    disX = x - b.x;
    disY = y - b.y;
    T distance = std::sqrt(disX * disX + disY * disY);
    return distance;
}

template <class T>
Vector2<T> Vector2<T>::operator + (const Vector2<T> &p) const {
    return Vector2<T>(x + p.x, y + p.y);
}
template <class T>
Vector2<T> Vector2<T>::operator + (const f32 &num) const {
    return Vector2<T>(x + num, y + num);
}
template <class T>
Vector2<T> Vector2<T>::operator += (const Vector2<T> &p) {
    x = x + p.x; 
    y = y + p.y;
    return *this;
}
template <class T>
Vector2<T> Vector2<T>::operator += (const f32 &num) {
    x = x + num; 
    y = y + num;
    return *this;
}
template <class T>
Vector2<T> Vector2<T>::operator - (const Vector2<T> &p) const {
    return Vector2<T>(x - p.x, y - p.y);
}
template <class T>
Vector2<T> Vector2<T>::operator - (const f32 &num) const {
    return Vector2<T>(x - num, y - num);
}
template <class T>
Vector2<T> Vector2<T>::operator -= (const Vector2<T> &p) {
    x = x - p.x; 
    y = y - p.y;
    return *this;
}
template <class T>
Vector2<T> Vector2<T>::operator -= (const f32 &num) {
    x = x - num; 
    y = y - num;
    return *this;
}
template <class T>
Vector2<T> Vector2<T>::operator / (const f32 &num) const {
    return Vector2<T>(x / num, y / num);
}
template <class T>
Vector2<T> Vector2<T>::operator * (const f32 &num) const{
    return Vector2<T>(x * num, y * num);
}

template <class T>
bool Vector2<T>::operator ==(const Vector2<T> &p) {
    return (x == p.x && y == p.y);
}
template <class T>
bool Vector2<T>::operator !=(const Vector2<T> &p) {
    return (x != p.x || y != p.y);
}

template class Vector2<i32>;
template class Vector2<f32>;