#include "Rect.h"

template <class T>
Rect<T>::Rect(T rX, T rY, T rW, T rH) {
    x = rX;
    y = rY;
    w = rW;
    h = rH;
}

template <class T>
Rect<T>::Rect(core::rect<T> rect){
    x = rect.UpperLeftCorner.X;
    y = rect.UpperLeftCorner.Y;
    w = rect.getWidth();
    h = rect.getHeight();
}

template <class T>
Rect<T>::Rect(const Rect<T>& rect) {
    x = rect.x;
    y = rect.y;
    w = rect.w;
    h = rect.h;
}

template <class T>
Rect<T>::~Rect() {
    
}

template <class T>
void Rect<T>::setRect(T rX, T rY, T rW, T rH){
    x = rX;
    y = rY;
    w = rW;
    h = rH;
}

template <class T>
void Rect<T>::setRect(core::rect<T> rect){
    x = rect.UpperLeftCorner.X;
    y = rect.UpperLeftCorner.Y;
    w = rect.getWidth();
    h = rect.getHeight();
}

template <class T>
core::rect<T> Rect<T>::getRect() {
    return core::rect<T>(core::vector2d<T>(x, y), core::dimension2d<T>(w, h));
}

template class Rect<int>;
template class Rect<float>;