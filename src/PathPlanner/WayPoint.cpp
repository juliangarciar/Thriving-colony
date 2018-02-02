#include "WayPoint.h"
// NavNode methods
NavNode::~NavNode(){

}
int NavNode::getIndex(){
    return this->m_index;
}

void NavNode::setIndex(int newIndex){
    this->m_index = newIndex;
}

// LWayPoint methods
LWayPoint::~LWayPoint(){

}
Vector2<float> LWayPoint::getPosition(){
    return this->m_vPosition;
}
void LWayPoint::setPosition(Vector2<float> position){
    this->m_vPosition = position;
}