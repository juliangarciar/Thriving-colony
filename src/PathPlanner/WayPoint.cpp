#include "WayPoint.h"
#define MAX_MAP 10240
#define TOTAL 80
// NavNode methods
NavNode::~NavNode(){

}
i32 NavNode::getIndex(){
    return this->m_index;
}

void NavNode::setIndex(i32 newIndex){
    this->m_index = newIndex;
}

LWayPoint::LWayPoint(Vector2<f32> position){
    m_vPosition = position;
    cellIndex = (i32)(TOTAL * position.x / MAX_MAP) + 
                ((i32)((TOTAL) * position.y / MAX_MAP) * TOTAL);

    if (cellIndex > TOTAL * TOTAL - 1) 
        cellIndex = TOTAL * TOTAL - 1;

}
// LWayPoint methods
LWayPoint::~LWayPoint(){

}
Vector2<f32> LWayPoint::getPosition(){
    return this->m_vPosition;
}
void LWayPoint::setPosition(Vector2<f32> position){
    this->m_vPosition = position;
}

i32 LWayPoint::getCellIndex(){
    return cellIndex;
}
void LWayPoint::setCellIndex(i32 index){
    cellIndex = index;
}