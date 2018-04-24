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
void Rect2D<T>::setRect2D(T rX, T rY, T rW, T rH) {
    x = rX;
    y = rY;
    w = rW;
    h = rH;
}

template <class T>
Rect2D<T> Rect2D<T>::getFixed() {
    i32 initialWidth = Window::Instance() -> getInitialWindowWidth();
    i32 initialHeight = Window::Instance() -> getInitialWindowHeight();
    i32 actualWidth = Window::Instance() -> getRealWindowWidth();
    i32 actualHeight = Window::Instance() -> getRealWindowHeight();

    i32 newX = x*actualWidth/initialWidth; 
    i32 newY = y*actualHeight/initialHeight; 
    i32 newW = w*actualWidth/initialWidth; 
    i32 newH = h*actualHeight/initialHeight; 

    return Rect2D<T>(newX, newY, newW, newH);
}

template class Rect2D<i32>;
template class Rect2D<f32>;