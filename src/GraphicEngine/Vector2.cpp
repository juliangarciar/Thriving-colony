#include "Vector2.h"
#include "Window.h"

template <class T>
Vector2<T>::Vector2() {
    x = 0;
    y = 0;
}

template <class T>
Vector2<T>::Vector2(T x, T y) {
    x = x;
    y = y;
}

template <class T>
Vector2<T>::Vector2(core::vector2di v) {
    x = v.X;
    y = v.Y;
}

template <class T>
Vector2<T>::Vector2(core::vector2df v) {
    x = v.X;
    y = v.Y;
}

template <class T>
Vector2<T>::~Vector2() {
    
}

template <class T>
void Vector2<T>::set(T x, T y) {
    x = x;
    y = y;
}

template <class T>
void Vector2<T>::set(core::vector2di v) {
    x = v.X;
    y = v.Y;
}

template <class T>
void Vector2<T>::set(core::vector2df v) {
    x = v.X;
    y = v.Y;
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
Vector2<T> Vector2<T>::getFromPolarCoordinates(float r, float phi) {
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

template <class T>
Vector2<T> Vector2<T>::getFixed() {
    int initialWidth = Window::Instance() -> getInitialWindowWidth();
    int initialHeight = Window::Instance() -> getInitialWindowHeight();
    int actualWidth = Window::Instance() -> getRealWindowWidth();
    int actualHeight = Window::Instance() -> getRealWindowHeight();

    int newX = x*actualWidth/initialWidth; 
    int newY = y*actualHeight/initialHeight; 

    return Vector2<T>(newX, newY);
}

template class Vector2<int>;
template class Vector2<float>;