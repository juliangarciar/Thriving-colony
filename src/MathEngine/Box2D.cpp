#include "Box2D.h"
Box2D::Box2D(){

}
Box2D::Box2D(f32 sizeX, f32 sizeY){
    halfSizeX = sizeX;
    halfSizeY = sizeY;
}
Box2D::Box2D(Vector2<f32> tl, Vector2<f32> br){
    halfSizeX = std::abs((br.x - tl.x) / 2);
    halfSizeY = std::abs((br.y - tl.y) / 2);
    m_vTopLeft = tl;
    m_vBottomRight = br;
    m_vCenter = (tl + br) / 2;
    m_vTopRight.x = br.x;
    m_vTopRight.y = tl.y;
    m_vBottomLeft.x = tl.x;
    m_vBottomLeft.y = br.y;
}
//Box2D::Box2D(Vector2<f32> _pos, f32 halfsize){
//    
//}
void Box2D::moveHitbox(f32 x, f32 y){
    m_vCenter.x = x;
    m_vCenter.y = y;

    m_vTopLeft.x = x - halfSizeX;
    m_vTopLeft.y = y - halfSizeY;

    m_vTopRight.x = x + halfSizeX;
    m_vTopRight.y = m_vTopLeft.y;

    m_vBottomLeft.x = m_vTopLeft.x;
    m_vBottomLeft.y = y + halfSizeY;

    m_vBottomRight.x = m_vTopRight.x;
    m_vBottomRight.y = m_vBottomLeft.y;

    //std::cout << "HalfSizeX: " << halfSizeX << " HalfSizeY: " << halfSizeY << "\n"; 
}
void Box2D::moveHitbox(Vector2<f32> _vectorPos){
    m_vCenter = _vectorPos;

    m_vTopLeft.x = _vectorPos.x - halfSizeX;
    m_vTopLeft.y = _vectorPos.y - halfSizeY;

    m_vTopRight.x = _vectorPos.x + halfSizeX;
    m_vTopRight.y = m_vTopLeft.y;

    m_vBottomLeft.x = m_vTopLeft.x;
    m_vBottomLeft.y = _vectorPos.y + halfSizeY;

    m_vBottomRight.x = m_vTopRight.x;
    m_vBottomRight.y = m_vBottomLeft.y;
}
/* TODO: Check this method, maybe is missfunctional */
bool Box2D::isOverlappedWith(Box2D other){
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
f32 Box2D::Top(){
    return m_vTopLeft.y;
}
f32 Box2D::Left(){
    return m_vTopLeft.x;
}
f32 Box2D::Bottom(){
    return m_vBottomRight.y;
}
f32 Box2D::Right(){
    return m_vBottomRight.x;
}
Box2D Box2D::getAmplifiedBox(f32 distance){
    Vector2<f32> amp = Vector2<f32>(distance, distance);
    Vector2<f32> tL = m_vTopLeft - amp;
    Vector2<f32> bR = m_vBottomRight + amp;
    Box2D dummy = Box2D(tL, bR);
    return dummy;
}