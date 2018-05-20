#include "Box2D.h"

Box2D::Box2D():m_vTopLeft(0, 0),
               m_vBottomRight(0, 0),
               m_vCenter(0, 0),
               m_vTopRight(0, 0),
               m_vBottomLeft(0, 0)
{}

Box2D::Box2D(Vector2<f32> vectorPosition, f32 sizeX, f32 sizeY):m_vTopLeft(0, 0),
                                                                m_vBottomRight(0, 0),
                                                                m_vCenter(0, 0),
                                                                m_vTopRight(0, 0),
                                                                m_vBottomLeft(0, 0)
{}

Box2D::Box2D(Vector2<f32> tl, Vector2<f32> br):m_vTopLeft(tl),
                                               m_vBottomRight(br),
                                               m_vCenter((tl + br) / 2.0f),
                                               m_vTopRight(br.x, tl.y),
                                               m_vBottomLeft(tl.x, br.y),
                                               cellsX((tl.x - br.y) / cSize),
                                               cellsY((tl.y - br.y) / cSize)
{}

void Box2D::moveHitbox(f32 x, f32 y) {
    Vector2<f32> vectorDirection = Vector2<f32>(x, y) - m_vCenter;
    
    m_vCenter += vectorDirection;
    m_vTopLeft += vectorDirection;
    m_vTopRight += vectorDirection;
    m_vBottomLeft += vectorDirection;
    m_vBottomRight += vectorDirection;
}

void Box2D::moveHitbox(Vector2<f32> _vectorPos) {
    Vector2<f32> vectorDirection = _vectorPos - m_vCenter;

    m_vCenter += vectorDirection;
    m_vTopLeft += vectorDirection;
    m_vTopRight += vectorDirection;
    m_vBottomLeft += vectorDirection;
    m_vBottomRight += vectorDirection;
}

bool Box2D::isOverlappedWith(const Box2D& other) const{
    return !((other.Top() >= Bottom()) ||
             (other.Bottom() <= Top()) ||
             (other.Left() >= Right()) ||
             (other.Right() <= Left()));
}

bool Box2D::isOverlappedWith(Vector2<f32> point) const{
    if (point.x <= Left() || point.x >= Right()) {
        return false;
    }
    if (point.y <= Bottom() || point.y >= Top()) {
        return false;
    }
    return true;
    //return (point.x > Left() && point.x < Right() && point.y > Bottom() && point.y < Top());
}

f32 Box2D::getHalfSize() const{
    return ((Right() - Left()) / 2.0f);
}

Vector2<f32> Box2D::TopLeft() const{
    return m_vTopLeft;
}

Vector2<f32> Box2D::BottomRight() const{
    return m_vBottomRight;
}

Vector2<f32> Box2D::Center() const{
    return m_vCenter;
}

Vector2<f32> Box2D::TopRight() const{ 
    return m_vTopRight;
}

Vector2<f32> Box2D::BottomLeft() const{
    return m_vBottomLeft;
}

f32 Box2D::Top() const{
    return m_vTopLeft.y;
}

f32 Box2D::Left() const{
    return m_vTopLeft.x;
}

f32 Box2D::Bottom() const{
    return m_vBottomRight.y;
}

f32 Box2D::Right() const{
    return m_vBottomRight.x;
}

Box2D Box2D::getAmplifiedBox(f32 distance) const{
    Vector2<f32> tL = m_vTopLeft - distance;
    Vector2<f32> bR = m_vBottomRight + distance;
    Box2D dummy(tL, bR);
    return dummy;
}

i32 Box2D::getCellsX() const{
    return cellsX;
}

i32 Box2D::getCellsY() const{
    return cellsY;
}