#include "Vector3.h"

template <class T>
Vector3<T>::Vector3() {
    
}

template <class T>
Vector3<T>::~Vector3() {
    
}

template <class T>
core::vector3df Vector3<T>::getVector() {
    return core::vector3df(x, y, z);
}

template class Vector3<int>;
template class Vector3<float>;