#include "WayPoint.h"
WayPoint::WayPoint(){
    
}
WayPoint::WayPoint(Vector2<f32> position){
    m_vPosition = position;
}
WayPoint::~WayPoint(){

}
Vector2<f32> WayPoint::getPosition(){
    return this->m_vPosition;
}
void WayPoint::setPosition(Vector2<f32> position){
    this->m_vPosition = position;
}

i32 WayPoint::getCellIndex(){
    return cellIndex;
}
void WayPoint::setCellIndex(i32 index){
    cellIndex = index;
}
i32 WayPoint::getIndex(){
    return m_index;
}
void WayPoint::setIndex(i32 index){
    m_index = index;
}