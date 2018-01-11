#include "Rect2D.h"
#include <GraphicEngine/Window.h>

template <class T>
Rect2D<T>::Rect2D(T rX, T rY, T rW, T rH) {
    x = rX;
    y = rY;
    w = rW;
    h = rH;
}

template <class T>
Rect2D<T>::Rect2D(core::rect<T> rect){
    x = rect.UpperLeftCorner.X;
    y = rect.UpperLeftCorner.Y;
    w = rect.getWidth();
    h = rect.getHeight();
}

template <class T>
Rect2D<T>::Rect2D(const Rect2D<T>& rect) {
    x = rect.x;
    y = rect.y;
    w = rect.w;
    h = rect.h;
}

template <class T>
Rect2D<T>::~Rect2D() {
    
}

template <class T>
void Rect2D<T>::setRect2D(T rX, T rY, T rW, T rH){
    x = rX;
    y = rY;
    w = rW;
    h = rH;
}

template <class T>
void Rect2D<T>::setRect2D(core::rect<T> rect){
    x = rect.UpperLeftCorner.X;
    y = rect.UpperLeftCorner.Y;
    w = rect.getWidth();
    h = rect.getHeight();
}

template <class T>
Rect2D<T> Rect2D<T>::getFixed(){
    int initialWidth = Window::Instance()->getInitialWindowWidth();
    int initialHeight = Window::Instance()->getInitialWindowHeight();
    int actualWidth = Window::Instance()->getRealWindowWidth();
    int actualHeight = Window::Instance()->getRealWindowHeight();

    int newX = x*actualWidth/initialWidth; 
    int newY = y*actualHeight/initialHeight; 
    int newW = w*actualWidth/initialWidth; 
    int newH = h*actualHeight/initialHeight; 

    return Rect2D<T>(newX, newY, newW, newH);
}

template <class T>
core::rect<T> Rect2D<T>::getRect2D() {
    return core::rect<T>(core::vector2d<T>(x, y), core::dimension2d<T>(w, h));
}

template class Rect2D<int>;
template class Rect2D<float>;