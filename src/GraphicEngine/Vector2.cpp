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
Vector2<T>::~Vector2() {
    
}

template <class T>
core::vector2di Vector2<T>::getVectorI() {
    return core::vector2di(x, y);
}

template <class T>
core::vector2df Vector2<T>::getVectorF() {
    return core::vector2df(x, y);
}

template class Vector2<int>;
template class Vector2<float>;