#include "Vector2.h"

template <class T>
Vector2<T>::Vector2() {
    this->x = 0;
    this->y = 0;
}

template <class T>
Vector2<T>::Vector2(T x, T y) {
    this->x = x;
    this->y = y;
}

template <class T>
Vector2<T>::Vector2(core::vector2di v){
    this->x = v.X;
    this->y = v.Y;
}

template <class T>
Vector2<T>::Vector2(core::vector2df v){
    this->x = v.X;
    this->y = v.Y;
}

template <class T>
Vector2<T>::~Vector2() {
    
}

template <class T>
void Vector2<T>::set(T x, T y){
    this->x = x;
    this->y = y;
}

template <class T>
void Vector2<T>::set(core::vector2di v){
    this->x = v.X;
    this->y = v.Y;
}

template <class T>
void Vector2<T>::set(core::vector2df v){
    this->x = v.X;
    this->y = v.Y;
}

template <class T>
Vector2<T>& Vector2<T>::normalize() {
    f64 length = x*x + y*y;
    // this check isn't an optimization but prevents getting NAN in the sqrt.
    if (length == 0) return *this;
        
    length = core::reciprocal_squareroot(length);

    x = (T)(x * length);
    y = (T)(y * length);
    return *this;
}

template <class T>
core::vector2di Vector2<T>::getVectorI() {
    return core::vector2di(x, y);
}

template <class T>
core::vector2df Vector2<T>::getVectorF() {
    return core::vector2df(x, y);
}

template <class T>
Vector2<T> Vector2<T>::getFromPolarCoordinates(float r, float phi){
    phi = phi * (PI/180);
    Vector2<T> point;
    point.x = x + (r * cosf(phi));  // Assign to the point member x
    point.y = y + (r * sinf(phi));  // Assign to the point member y.
    return point;
}

template class Vector2<int>;
template class Vector2<float>;