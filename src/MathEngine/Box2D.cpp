#include "Box2D.h"
Box2D::Box2D(){
    
}
Box2D::Box2D(Vector2<f32> tl, Vector2<f32> br){
    m_vTopLeft = tl;
    m_vBottomRight = br;
    m_vCenter = (tl + br) / 2;
    m_vTopRight.x = br.x;
    m_vTopRight.y = tl.y;
    m_vBottomLeft.x = tl.x;
    m_vBottomLeft.y = br.y;
    //m_vTopLeft(tl),
    //m_vBottomRight(br),
    //m_vCenter((tl+br)/2.0),
    //m_vTopRight(Vector2<f32>(br.x, tl.y)),
    //m_vBottomLeft(Vector2<f32>(tl.x, br.y))

}
bool Box2D::isOverlappedWith(Box2D& other){
    return !((other.Top() > this->Bottom()) ||
        (other.Bottom() < this->Top()) ||
        (other.Left() > this->Right()) ||
        (other.Right() < this->Left()));
}
Vector2<f32> Box2D::TopLeft(){
    return m_vTopLeft;
}
Vector2<f32> Box2D::BottomRight(){
    return m_vBottomRight;
}
Vector2<f32> Box2D::Center(){
    return m_vCenter;
}
Vector2<f32> Box2D::TopRight(){
    return m_vTopRight;
}
Vector2<f32> Box2D::BottomLeft(){
    return m_vBottomLeft;
}
double    Box2D::Top(){
    return m_vTopLeft.y;
}
double    Box2D::Left(){
    return m_vTopLeft.x;
}
double    Box2D::Bottom(){
    return m_vBottomRight.y;
}
double    Box2D::Right(){
    return m_vBottomRight.x;
}