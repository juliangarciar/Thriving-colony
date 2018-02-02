#include "WayPoint.h"
NavNode::~NavNode(){

}
int NavNode::getIndex(){
    return this->m_index;
}
void NavNode::setIndex(int newIndex){
    this->m_index = newIndex;
}
LWayPoint::LWayPoint(Vector2<float> position){
    this->m_vPosition = position;
}
LWayPoint::~LWayPoint(){

}
Vector2<float> LWayPoint::getPosition(){
    return this->m_vPosition;
}