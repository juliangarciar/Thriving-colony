#include "Edge.h"
Edge::~Edge(){
    
}

i32 Edge::getFrom(){
    return this->m_iFrom;
}
void Edge::setFrom(i32 newIndex){
    this->m_iFrom = newIndex;
}

i32 Edge::getTo(){
    return this->m_iTo;
}
void Edge::setTo(i32 newIndex){
    this->m_iTo = newIndex;
}

f32 Edge::getCost(){
    return this->m_tCost;
}
void Edge::setCost(f32 newCost){
    this->m_tCost = newCost;
}