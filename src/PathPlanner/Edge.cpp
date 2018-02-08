#include "Edge.h"
Edge::~Edge(){
    
}

int Edge::getFrom(){
    return this->m_iFrom;
}
void Edge::setFrom(int newIndex){
    this->m_iFrom = newIndex;
}

int Edge::getTo(){
    return this->m_iTo;
}
void Edge::setTo(int newIndex){
    this->m_iTo = newIndex;
}

float Edge::getCost(){
    return this->m_tCost;
}
void Edge::setCost(float newCost){
    this->m_tCost = newCost;
}