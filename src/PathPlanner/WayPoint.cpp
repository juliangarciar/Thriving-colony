#include "WayPoint.h"
// NavNode methods
NavNode::~NavNode(){

}
i32 NavNode::getIndex(){
    return this->m_index;
}

void NavNode::setIndex(i32 newIndex){
    this->m_index = newIndex;
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